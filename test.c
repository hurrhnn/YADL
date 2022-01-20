/*
 YADL is a Yet Another Discord Library, written from the scratch.
 This file is part of YADL.

 Copyright (C) 2021 Rhnn Hur (hurrhnn), Wonjun Jung (KokoseiJ)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <dlfcn.h>
#include "src/yadl.h"

unsigned char *provide_20ms_raw_audio_callback(void *args) {
    int *fd = args;
    struct timeval timeout;
    fd_set read_fds;
    unsigned char *pcm_bytes = yadl_malloc(YADL_VOICE_UDP_CLIENT_OPUS_FRAME_SIZE * YADL_VOICE_UDP_CLIENT_OPUS_CHANNELS * YADL_WORD);

    timeout.tv_sec = 0;
    timeout.tv_usec = 5 * 1000;

    FD_ZERO(&read_fds);
    FD_SET(*fd, &read_fds);
    int res = select(*fd + 1, &read_fds, NULL, NULL, &timeout);

    /* return empty audio data if socks timeout. */
    if (res > 0) {
        /* Read a 16 bits/sample audio frame. */
        read(*fd, pcm_bytes, YADL_VOICE_UDP_CLIENT_OPUS_FRAME_SIZE * YADL_VOICE_UDP_CLIENT_OPUS_CHANNELS * YADL_WORD);
    }

    return pcm_bytes;
}

void on_ready(const struct yadl_event_on_ready *event) {
    printf("YADL v%s Library Test Started.\n\n", YADL_VERSION);
    application_t *application = yadl_retrieve_application_info(event->context);
    user_t *bot_admin = yadl_retrieve_user_by_id(event->context, application->owner->id);

    puts("===== On Ready =====");
    printf("Bot Owner: %s#%s\n", bot_admin->username, bot_admin->discriminator);
    printf("Gateway Version: %d\n", event->gateway_version);
    printf("ID: %s\n", event->self_user->id);
    printf("Name: %s#%s\n", event->self_user->username, event->self_user->discriminator);
    printf("Guild Count: %d\n", event->unavailable_guild_count);
    puts("");

    printf("Application Team Name: %s\n", application->team->name);

    yadl_application_flags_t application_flags = {.value = application->flags};
    printf("\nApplication Flags - GATEWAY_PRESENCE: %d\n"
           "                    GATEWAY_PRESENCE_LIMITED: %d\n"
           "                    GATEWAY_GUILD_MEMBERS: %d\n"
           "                    GATEWAY_GUILD_MEMBERS_LIMITED: %d\n"
           "                    GATEWAY_MESSAGE_CONTENT: %d\n"
           "                    GATEWAY_MESSAGE_CONTENT_LIMITED: %d\n"
           "                    VERIFICATION_PENDING_GUILD_LIMIT: %d\n"
           "                    EMBEDDED: %d\n\n",

           application_flags.flags.GATEWAY_PRESENCE, application_flags.flags.GATEWAY_PRESENCE_LIMITED,
           application_flags.flags.GATEWAY_GUILD_MEMBERS, application_flags.flags.GATEWAY_GUILD_MEMBERS_LIMITED,
           application_flags.flags.GATEWAY_MESSAGE_CONTENT, application_flags.flags.GATEWAY_MESSAGE_CONTENT_LIMITED,
           application_flags.flags.VERIFICATION_PENDING_GUILD_LIMIT, application_flags.flags.EMBEDDED);

    for (int i = 0; i < application->team->members->size; i++)
        printf("Team Member %02d: %s#%s\n", i + 1,
               ((team_member_t *) application->team->members->array[i])->user->username,
               ((team_member_t *) application->team->members->array[i])->user->discriminator);
    puts("");
}

void on_direct_message_create(const struct yadl_event_on_direct_message_create *event) {
    printf("[DIRECT_MESSAGE][%s#%s]: %s\n", event->author->username, event->author->discriminator,
           event->message->content);
}

void on_guild_create(const struct yadl_event_on_guild_create *event) {
    puts("===== On Guild Create =====");
    printf("Guild Name: %s, %s\n", event->guild->name, event->guild->id);
    printf("Guild Member Count: %d\n\n", event->guild->member_count);
}

void on_guild_message_create(const struct yadl_event_on_guild_message_create *event) {
    char *content = event->message->content;
    if (strlen(content) && strcmp(event->author->id, event->context->self_user->id) != 0) {
        printf("[GUILD_MESSAGE][%s][%s][%s][%s#%s]: %s\n", event->message->timestamp,
               event->guild->name,
               event->channel->name,
               event->author->username,
               event->author->discriminator,
               content);

        bool is_install = false;
        if ((is_install = (!strcmp(content, "!!install"))) ||
            (!strcmp(content, "!!uninstall"))) {
            if (is_install) {
                event->context->user_data = event->channel->id;
                yadl_create_message(event->context, event->channel->id, "`Successfully Installed.`",
                                    false, NULL, NULL, NULL, NULL, NULL);
            } else {
                event->context->user_data = NULL;
                yadl_create_message(event->context, event->channel->id, "`Successfully Uninstalled.`",
                                    false, NULL, NULL, NULL, NULL, NULL);
            }

        } else if (strstr(content, "!!file ")) {
            application_t *application = yadl_retrieve_application_info(event->context);
            for (int i = 0; i < application->team->members->size; i++) {
                if (!strcmp(((team_member_t *) application->team->members->array[i])->user->id, event->author->id)) {
                    char *parse_pos = strstr(content, "!!file "), *file_name =
                            parse_pos + strlen("!!file ");
                    if (parse_pos != NULL) {
                        FILE *fp;
                        if ((fp = fopen(file_name, "r")) == NULL) {
                            yadl_create_message(event->context, event->channel->id,
                                                yadl_strcat(file_name, " file not found."),
                                                false, NULL, NULL, NULL, NULL, NULL);
                            return;
                        }

                        yadl_object_array_t *attachments = yadl_malloc(sizeof(yadl_object_array_t));
                        yadl_object_array_t *files = yadl_malloc(sizeof(yadl_object_array_t));

                        attachments->array = yadl_malloc(sizeof(void *));
                        files->array = yadl_malloc(sizeof(void *));
                        attachments->size = files->size = 1;

                        attachment_t *attachment = yadl_malloc(sizeof(attachment_t));
                        attachment->filename = yadl_get_file_name_from_path(file_name);
                        attachment->description = "TEST!";
                        attachment->size = yadl_get_file_size(fp);
                        attachments->array[0] = attachment;

                        unsigned char *file_data = yadl_malloc(attachment->size);
                        fread(file_data, attachment->size, 1, fp);
                        fclose(fp);
                        files->array[0] = file_data;

                        char *send_content = yadl_malloc(YADL_MIDIUM_SIZE);
                        sprintf(send_content, "`File: %s`", file_name);

                        yadl_create_message(event->context, event->channel->id, send_content,
                                            false, NULL, NULL, NULL, attachments, files);
                        return;
                    }
                }
            }
            message_reference_t *reference = yadl_malloc(sizeof(message_reference_t));
            reference->message_id = event->message_id;

            embed_t *embed = yadl_malloc(sizeof(embed_t));
            embed->title = "Permission denied.";
            embed->description = "Only members of the application team can use it.";

            yadl_object_array_t *embeds = yadl_malloc(sizeof(yadl_object_array_t));
            embeds->array = yadl_malloc(sizeof(void *));
            embeds->array[0] = embed;
            embeds->size = 1;

            yadl_create_message(event->context, event->channel->id, NULL, false,
                                embeds, NULL, reference, NULL, NULL);

        } else if (strstr(content, "ㅠㅠ") || strstr(content, "bb")) {
            embed_image_t *embed_image = yadl_malloc(sizeof(embed_image_t));
            embed_image->url = "https://media.discordapp.net/attachments/686272875010850857/900913724183941170/nichijou.gif";

            embed_t *embed = yadl_malloc(sizeof(embed_t));
            char *title = yadl_malloc(YADL_MIDIUM_SIZE);
            sprintf(title, "%s님이 슬퍼 합니다 ㅠㅠ",
                    event->member->nick == NULL ? event->author->username : event->member->nick);
            embed->title = title;
            embed->color = 0x0F52BA;
            embed->image = embed_image;

            yadl_object_array_t *embeds = yadl_malloc(sizeof(yadl_object_array_t));
            embeds->array = yadl_malloc(sizeof(void *));
            embeds->array[0] = embed;
            embeds->size = 1;

            yadl_create_message(event->context, event->channel->id, NULL, false,
                                embeds, NULL, NULL, NULL, NULL);
        } else if (strstr(content, "고양이") || strstr(content, "애옹") || strstr(content, "cat")) {
            http_result_t *result = http_request("GET", "https://rcat.ch1ck.xyz/meow/fake.png", NULL, NULL,
                                                 event->context->info.USER_AGENT, NULL, 0);

            yadl_object_array_t *attachments = yadl_malloc(sizeof(void *)), *files = yadl_malloc(sizeof(void *));
            attachments->array = yadl_malloc(sizeof(void *)), files->array = yadl_malloc(sizeof(void *));
            attachments->size = files->size = 1;

            attachment_t *attachment = yadl_malloc(sizeof(attachment_t));
            attachment->id = 0;
            attachment->filename = "random_cat.png";
            attachment->size = result->response_size;

            attachments->array[0] = attachment;
            files->array[0] = *result->response_body;

            yadl_create_message(event->context, event->channel->id,
                                NULL, false, NULL, NULL, NULL, attachments, files);
        } else if (strstr(content, ";;")) {
            yadl_create_message(event->context, event->channel->id, "하라는 코딩은 안하고!",
                                false, NULL, NULL, NULL, NULL, NULL);
        } else if (strstr(content, "!!eval")) {
            void *ptr = strstr(content, "!!eval") + strlen("!!eval");

            FILE *fp;
            if ((fp = fopen("eval.c", "w")) == NULL)
                return;

            char init_code[] = "#include \"../src/yadl.h\"\n\n"
                               "void eval(const struct yadl_event_on_guild_message_create *event) {\n"
                               "lws_set_log_level(LLL_ERR | LLL_WARN, NULL);\n";

            fwrite(init_code, strlen(init_code), 1, fp);
            fwrite(ptr, strlen(ptr), 1, fp);
            fwrite("\n}", strlen("\n}"), 1, fp);
            fclose(fp);

            yadl_object_array_t *embeds = yadl_malloc(sizeof(yadl_object_array_t));
            embeds->array = yadl_malloc(sizeof(void *));

            FILE *pp;
            if ((pp = popen(
                    "clang -c -fPIC -I/opt/homebrew/opt/openssl/include -Iinstall/include eval.c -o eval.o 2>&1",
                    "r")) == NULL)
                return;

            char buffer[5900] = {0x0};
            while (fread(buffer, 1, 5900, pp) != 0) {
                embed_t *embed = yadl_malloc(sizeof(embed_t));

                embed->type = "rich";
                embed->description = yadl_malloc(5900);
                strcpy(embed->description, "```\n");
                strcpy(embed->description + 4, buffer);
                strcpy(embed->description + strlen(embed->description), "\n```");
                embeds->array[embeds->size++] = embed;

                memset(buffer, 0x0, 5900);
            }

            int ret = pclose(pp);
            ret = WEXITSTATUS(ret);

            if (ret != 0) {
                char *error = yadl_malloc(YADL_MIDIUM_SIZE);
                sprintf(error, "clang build error with return code %d", ret);
                for (int i = 0; i < embeds->size; i++)
                    ((embed_t *) embeds->array[i])->title = error;

                yadl_create_message(event->context, event->channel->id, NULL,
                                    false, embeds, NULL, NULL, NULL, NULL);
                return;
            }
            remove("eval.c");

            ret = system("clang -shared -o eval.so eval.o -L. -Linstall/lib -lYADL -lparson -lwebsockets");
            if (ret != 0) {
                char *error = yadl_malloc(YADL_MIDIUM_SIZE);
                sprintf(error, "`create .so library error with return code %d`", ret);
                yadl_create_message(event->context, event->channel->id, error,
                                    false, NULL, NULL, NULL, NULL, NULL);
                return;
            }
            remove("eval.o");

            void *handle = NULL;
            void *(*eval)(const struct yadl_event_on_guild_message_create *event) = NULL;
            if ((handle = dlopen("eval.so", RTLD_LAZY)) == NULL)
                return;

            eval = dlsym(handle, "eval");
            if (dlerror() != NULL) {
                dlclose(handle);
                return;
            }

            eval(event);
            dlclose(handle);
            remove("eval.so");
        } else if (strstr(content, "!!voice ")) {
            const char *fifo_pipe = yadl_strcat(event->guild->id, ".pipe");
            remove(fifo_pipe);
            mkfifo(fifo_pipe, 0777);

            int *fifo_fd = yadl_malloc(sizeof(int));
            *fifo_fd = open(fifo_pipe, O_RDWR);

            void *ptr = strstr(content, "!!voice ") + strlen("!!voice ");
            yadl_init_voice_client(event->context, get_list(event->context->guild_voice_channels, ptr),
                                   provide_20ms_raw_audio_callback, fifo_fd);
        }
    }
}

int main(__attribute__((unused)) int argc, char **argv) {
    yadl_context_t context;
    memset(&context, 0x0, sizeof(yadl_context_t));

    const char *token_env = getenv("TOKEN"); // get token from environment variable.
    if (token_env == NULL) {
        lwsl_err("Token not provided. please run `TOKEN=<token> %s`.", argv[0]);
        exit(EXIT_FAILURE);
    }
    memcpy(context.info.TOKEN, token_env, strlen(token_env));

    yadl_gateway_intents_t gateway_intents = {.value = YADL_GATEWAY_INTENTS_ALL};
    gateway_intents.flags.GUILD_MEMBERS = false;
    gateway_intents.flags.GUILD_PRESENCES = false;

    context.info.GATEWAY_INTENTS = gateway_intents.value;
    context.callbacks.on_ready = on_ready;
    context.callbacks.on_direct_message_create = on_direct_message_create;
    context.callbacks.on_guild_create = on_guild_create;
    context.callbacks.on_guild_message_create = on_guild_message_create;
    context.user_data = NULL;

    yadl_init(&context);
    yadl_launch(&context);

    yadl_cleanup(&context);
    return 0;
}
