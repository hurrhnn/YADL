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
#include "src/yadl.h"

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
    if (strcmp(event->author->id, event->context->self_user->id) != 0) {
        printf("[GUILD_MESSAGE][%s][%s][%s][%s#%s]: %s\n", event->message->timestamp,
               event->guild->name,
               event->channel->name,
               event->author->username,
               event->author->discriminator,
               event->message->content);

        bool is_install = false;
        if ((is_install = (!strcmp(event->message->content, "!!install"))) ||
            (!strcmp(event->message->content, "!!uninstall"))) {
            if (is_install) {
                event->context->user_data = event->channel->id;
                yadl_create_message(event->context, event->channel->id, "`Successfully Installed.`",
                                    false, NULL, NULL, NULL, NULL, NULL);
            } else {
                event->context->user_data = NULL;
                yadl_create_message(event->context, event->channel->id, "`Successfully Uninstalled.`",
                                    false, NULL, NULL, NULL, NULL, NULL);
            }

        } else if (strstr(event->message->content, "!!file ")) {
            application_t *application = yadl_retrieve_application_info(event->context);
            for (int i = 0; i < application->team->members->size; i++) {
                if (!strcmp(((team_member_t *) application->team->members->array[i])->user->id, event->author->id)) {
                    char *parse_pos = strstr(event->message->content, "!!file "), *file_name =
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

                        char *content = yadl_malloc(YADL_MIDIUM_SIZE);
                        sprintf(content, "`File: %s`", file_name);

                        yadl_create_message(event->context, event->channel->id, content, false,
                                            NULL, NULL, NULL, attachments, files);
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

            yadl_create_message(event->context, event->channel->id,
                                NULL, false, embeds, NULL, reference, NULL, NULL);

        } else if (strstr(event->message->content, "ㅠㅠ") || strstr(event->message->content, "bb")) {
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

            yadl_create_message(event->context, event->channel->id,
                                NULL, false, embeds, NULL, NULL, NULL, NULL);
        } else if (strstr(event->message->content, "고양이") || strstr(event->message->content, "애옹") ||
                   strstr(event->message->content, "cat")) {
            char **result = http_request("GET", "https://api.thecatapi.com/v1/images/search", NULL, NULL,
                                         event->context->info.USER_AGENT, NULL, 0)->response_body;
            JSON_Array *cat_data = yadl_json_array_builder(*result);
            yadl_create_message(event->context, event->channel->id,
                                json_object_get_string(json_array_get_object(cat_data, 0), "url"), false, NULL, NULL,
                                NULL, NULL, NULL);
        } else if (strstr(event->message->content, ";;")) {
            yadl_create_message(event->context, event->channel->id, "하라는 코딩은 안하고!",
                                false, NULL, NULL, NULL, NULL, NULL);
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
