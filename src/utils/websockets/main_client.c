/*
 YADL is Yet Another Discord Library, written from the scratch.
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

#include "main_client.h"

static const u_int32_t backoff_ms[] = {1000, 2000, 3000, 4000, 5000 };

static const lws_retry_bo_t retry = {
        .retry_ms_table            = backoff_ms,
        .retry_ms_table_count        = LWS_ARRAY_SIZE(backoff_ms),
        .conceal_count            = LWS_ARRAY_SIZE(backoff_ms),

        .secs_since_valid_ping        = 3,  /* force PINGs after secs idle */
        .secs_since_valid_hangup    = 10, /* hangup after secs idle */

        .jitter_percent            = 20,
};

void connection_retry(struct lws *client_wsi, lws_sorted_usec_list_t *sul, sul_cb_t callback, u_int16_t *retry_count);

void schedule_callback(lws_sorted_usec_list_t *sul) {
    yadl_pthread_append(pthread_self());
    struct main_client_payload *main_payload = lws_container_of(sul, struct main_client_payload, sul);
    struct lws_client_connect_info i;
    memset(&i, 0, sizeof(i));

    i.context = main_payload->context;
    i.port = 443;
    i.address = main_payload->address;
    i.path = main_payload->path;
    i.host = i.address;
    i.ssl_connection = LCCSCF_USE_SSL;
    i.pwsi = &main_payload->client_wsi;
    i.retry_and_idle_policy = &retry;
    i.userdata = main_payload;

    if (!lws_client_connect_via_info(&i))
        lws_retry_sul_schedule(main_payload->context, 0, sul, &retry, schedule_callback,
                               &main_payload->retry_count);
}

void connection_retry(struct lws *client_wsi, lws_sorted_usec_list_t *sul, sul_cb_t callback, u_int16_t *retry_count) {
    if (lws_retry_sul_schedule_retry_wsi(client_wsi, sul, callback, retry_count)) {
        lwsl_err("connection attempts exhausted.\n");
        ((struct main_client_payload *) lws_context_user(lws_get_context(client_wsi)))->connection_exhausted = true;
    }
}

void main_client_object_init(struct main_client_payload *main_client_payload) {
    if (main_client_payload->client_object == NULL) {
        main_client_payload->client_object = yadl_malloc(sizeof(struct main_client_object), true);
        *main_client_payload->client_object = (struct main_client_object) {yadl_malloc(sizeof(size_t), true),
                                                                           yadl_malloc(sizeof(size_t), true), NULL,
                                                                           yadl_malloc(sizeof(pthread_cond_t), true), NULL,
                                                                           yadl_malloc(sizeof(pthread_mutex_t), true), NULL,
                                                                           NULL,
                                                                           yadl_malloc(sizeof(int64_t), true),
                                                                           yadl_malloc(sizeof(self_user_t), true),
                                                                           NULL,
                                                                           yadl_malloc(YADL_MAIN_SESSION_ID_LENGTH, true)};

        pthread_cond_init(main_client_payload->client_object->main_client_cond, NULL);
        pthread_mutex_init(main_client_payload->client_object->main_client_mutex, NULL);
    }
}

void main_client_wait_signal(pthread_mutex_t *pthread_mutex, pthread_cond_t *pthread_cond, struct timespec *timespec) {
    if (timespec == NULL) {
        pthread_mutex_lock(pthread_mutex);
        pthread_cond_wait(pthread_cond, pthread_mutex);
        pthread_mutex_unlock(pthread_mutex);
    } else {
        pthread_mutex_lock(pthread_mutex);
        pthread_cond_timedwait(pthread_cond, pthread_mutex, timespec);
        pthread_mutex_unlock(pthread_mutex);
    }
}

void *main_send_heartbeat(void *ws_payload) {
    struct main_client_payload *p_ws_payload = ws_payload;
    struct timeval tv;
    struct timespec ts;
    while (!p_ws_payload->connection_exhausted) {
        JSON_Object *root_object = yadl_json_object_builder(NULL);
        json_object_dotset_number(root_object, "op", 1);
        json_object_dotset_number(root_object, "d", (double) (*p_ws_payload->client_object->heartbeat += 1));

        yadl_json_lws_write(p_ws_payload->client_wsi, root_object);

        gettimeofday(&tv, NULL);
        long future_us = tv.tv_usec + *p_ws_payload->client_object->heartbeat_interval * 1000;
        ts.tv_nsec = (future_us % 1000000) * 1000;
        ts.tv_sec = tv.tv_sec + future_us / 1000000;

        pthread_cond_signal(p_ws_payload->client_object->main_client_cond);
        main_client_wait_signal(p_ws_payload->client_object->main_heartbeat_mutex,
                                p_ws_payload->client_object->main_heartbeat_cond, &ts);
    }
    return NULL;
}

int main_websocket_callback(struct lws *wsi, enum lws_callback_reasons reason,
                            __attribute__((unused)) void *user, void *in, size_t len) {
    yadl_pthread_append(pthread_self());
    struct main_client_payload *ws_payload = lws_context_user(lws_get_context((wsi)));
    ws_payload->client_wsi = wsi;
    yadl_context_t *yadl_context = ws_payload->yadl_context;

    switch (reason) {
        case LWS_CALLBACK_WSI_CREATE: {
            main_client_object_init(ws_payload);
            break;
        }

        case LWS_CALLBACK_CLIENT_CONNECTION_ERROR: {
            lwsl_err("CLIENT_CONNECTION_ERROR: %s\n",
                     in ? (char *) in : "(null)");
            connection_retry(wsi, &ws_payload->sul, schedule_callback, &ws_payload->retry_count);
            break;
        }

        case LWS_CALLBACK_CLIENT_RECEIVE: {
//            lwsl_hexdump_level(LLL_USER, in, len);
            char *raw = json_serialize_to_string_pretty(json_parse_string(in));
            if (raw == NULL)
                break;

            JSON_Object *root_object = yadl_json_object_builder(raw);
//            printf("%s\n", raw);

            const char *type = json_object_dotget_string(root_object, "t");
            *ws_payload->client_object->sequence = (size_t) (json_object_dotget_number(root_object, "s") == 0
                                                             ? (double) *ws_payload->client_object->sequence
                                                             : json_object_dotget_number(root_object, "s"));
            u_int8_t op_code = (u_int8_t) json_object_dotget_number(root_object, "op");
            JSON_Object *data_object = json_object_dotget_object(root_object, "d");

            if (ws_payload->client_object->test != NULL && strstr(raw, ws_payload->client_object->self_user->id) == NULL) {
                char *create_message_api = yadl_malloc(YADL_MIDIUM_SIZE),
                        *authorization_header = yadl_malloc(YADL_MIDIUM_SIZE), **payload = yadl_malloc(sizeof(char *));
                snprintf(create_message_api, YADL_MIDIUM_SIZE,
                         yadl_strcat(yadl_context->info.API_URL, YADL_CREATE_MESSAGE_PATH),
                         ws_payload->client_object->test);
                snprintf(authorization_header, YADL_MIDIUM_SIZE, yadl_context->info.AUTHORIZATION_HEADER,
                         yadl_context->info.TOKEN);

                JSON_Object *message_payload = yadl_json_object_builder(NULL);
                char *pretty_raw = yadl_strcat(yadl_strcat("```json\n", raw), "\n```");
                char *content = yadl_malloc(2000);
                if (strlen(pretty_raw) >= 2000) {
                    memcpy(content, pretty_raw, 1991);
                    strcpy(content + 1991, " ...\n```");
                    json_object_dotset_string(message_payload, "content", content);
                } else
                    json_object_dotset_string(message_payload, "content", pretty_raw);

                *payload = json_serialize_to_string(json_object_get_wrapping_value(message_payload));
                http_request("POST", create_message_api, authorization_header, NULL, yadl_context->info.APPLICATION,
                             payload);
            }

            switch (op_code) {
                case 0: {
                    void *user_data = ws_payload->yadl_context->callbacks.user_data;
                    if (!strcmp(type, "READY")) {
                        ws_payload->client_object->self_user = parse_user(json_object_dotget_value(data_object, "user"));
                        memcpy(ws_payload->client_object->session_id, json_object_dotget_string(data_object, "session_id"), YADL_MAIN_SESSION_ID_LENGTH);

                        struct yadl_event_on_ready *on_ready = yadl_malloc(sizeof(struct yadl_event_on_ready));
                        JSON_Array *unavailable_guilds = json_object_dotget_array(data_object, "guilds");

                        on_ready->gateway_version = (int8_t) json_object_dotget_number(data_object, "v");
                        on_ready->self_user = ws_payload->client_object->self_user;
                        on_ready->unavailable_guild_count = json_array_get_count(unavailable_guilds);

                        for(int i = 0; i < on_ready->unavailable_guild_count; i++) {
                            guild_t *unavailable_guild = parse_guild(json_array_get_value(unavailable_guilds, i));
                            put_list(ws_payload->yadl_context->guilds, unavailable_guild->id, unavailable_guild);
                        }
                        ws_payload->yadl_context->callbacks.on_ready(on_ready, user_data);
                    }
                    else if (!strcmp(type, "GUILD_CREATE")) {
                        guild_t *guild = parse_guild(json_object_get_wrapping_value(data_object));
                        put_list(ws_payload->yadl_context->guilds, guild->id, guild);

                        struct yadl_event_on_guild_create *on_guild_create = yadl_malloc(sizeof(struct yadl_event_on_guild_create));
                        on_guild_create->guild = guild;
                        ws_payload->yadl_context->callbacks.on_guild_create(on_guild_create, user_data);
                    }
                    else if (!strcmp(type, "MESSAGE_CREATE")) {
                        // Below is the test code.
                        if (!strcmp(json_object_dotget_string(data_object, "content"), "!!install") && !strcmp(
                                json_object_dotget_string(data_object, "author.id"), "345473282654470146")) {
                            ws_payload->client_object->test = malloc(YADL_MIDIUM_SIZE);
                            memcpy(ws_payload->client_object->test,
                                   json_object_dotget_string(data_object, "channel_id"),
                                   strlen(json_object_dotget_string(data_object, "channel_id")));

                            char *create_message_api = yadl_malloc(YADL_MIDIUM_SIZE),
                                    *authorization_header = yadl_malloc(YADL_MIDIUM_SIZE), **payload = yadl_malloc(
                                    sizeof(char *));
                            snprintf(create_message_api, YADL_MIDIUM_SIZE,
                                     yadl_strcat(yadl_context->info.API_URL, YADL_CREATE_MESSAGE_PATH),
                                     ws_payload->client_object->test);
                            snprintf(authorization_header, YADL_MIDIUM_SIZE, yadl_context->info.AUTHORIZATION_HEADER,
                                     yadl_context->info.TOKEN);

                            JSON_Object *message_payload = yadl_json_object_builder(NULL);
                            json_object_dotset_string(message_payload, "content", "Successfully Installed.");

                            *payload = json_serialize_to_string(json_object_get_wrapping_value(message_payload));
                            http_request("POST", create_message_api, authorization_header, NULL,
                                         yadl_context->info.APPLICATION, payload);
                        } else if (!strcmp(json_object_dotget_string(data_object, "content"), "!!uninstall") && !strcmp(
                                json_object_dotget_string(data_object, "author.id"), "345473282654470146")) {
                            char *create_message_api = yadl_malloc(YADL_MIDIUM_SIZE),
                                    *authorization_header = yadl_malloc(YADL_MIDIUM_SIZE), **payload = yadl_malloc(
                                    sizeof(char *));
                            snprintf(create_message_api, YADL_MIDIUM_SIZE,
                                     yadl_strcat(yadl_context->info.API_URL, YADL_CREATE_MESSAGE_PATH),
                                     ws_payload->client_object->test);
                            snprintf(authorization_header, YADL_MIDIUM_SIZE, yadl_context->info.AUTHORIZATION_HEADER,
                                     yadl_context->info.TOKEN);

                            JSON_Object *message_payload = yadl_json_object_builder(NULL);
                            json_object_dotset_string(message_payload, "content", "Successfully Uninstalled.");

                            *payload = json_serialize_to_string(json_object_get_wrapping_value(message_payload));
                            http_request("POST", create_message_api, authorization_header, NULL,
                                         yadl_context->info.APPLICATION, payload);
                            ws_payload->client_object->test = NULL;
                        }
                    }
                    break;
                }
                case 9: {
                    ws_payload->client_object->invalid_session = true;
                    return -1; // Just returns -1 to disconnect.
                }
                case 10: {
                    *ws_payload->client_object->heartbeat_interval = (int64_t) json_object_dotget_number(root_object,
                                                                                                         "d.heartbeat_interval");

                    if (ws_payload->client_object->heartbeat_main == NULL) {
                        yadl_pthread_context_t *heartbeat_main_context = yadl_pthread_create(main_send_heartbeat,
                                                                                             NULL,ws_payload);

                        ws_payload->client_object->heartbeat_main = heartbeat_main_context->pthread;
                        ws_payload->client_object->main_heartbeat_cond = heartbeat_main_context->pthread_cond;
                        ws_payload->client_object->main_heartbeat_mutex = heartbeat_main_context->pthread_mutex;
                        lwsl_user("op %d, Started main heartbeat thread..", op_code);

                        main_client_wait_signal(ws_payload->client_object->main_client_mutex,
                                                ws_payload->client_object->main_client_cond, NULL);
                    } else {
                        pthread_cond_signal(ws_payload->client_object->main_heartbeat_cond);
                        lwsl_user("op %d, Sent signal to exist heartbeat thread..", op_code);

                        main_client_wait_signal(ws_payload->client_object->main_client_mutex,
                                                ws_payload->client_object->main_client_cond, NULL);
                    }

                    if(!ws_payload->client_object->invalid_session && strlen(ws_payload->client_object->session_id)) {
                        root_object = yadl_json_object_builder(NULL);
                        json_object_dotset_number(root_object, "op", 6);
                        json_object_dotset_string(root_object, "d.token", yadl_context->info.TOKEN);
                        json_object_dotset_string(root_object, "d.session_id", ws_payload->client_object->session_id);
                        json_object_dotset_number(root_object, "d.seq", (double) *ws_payload->client_object->sequence);

                        lwsl_user("%s\n", json_serialize_to_string(json_object_get_wrapping_value(root_object)));
                        yadl_json_lws_write(wsi, root_object);
                    } else {
                        ws_payload->client_object->invalid_session = false;
                        root_object = yadl_json_object_builder(NULL);
                        json_object_dotset_number(root_object, "op", 2);
                        json_object_dotset_string(root_object, "d.token", yadl_context->info.TOKEN);
                        json_object_dotset_string(root_object, "d.properties.$os", "Linux");
                        json_object_dotset_string(root_object, "d.properties.$browser", yadl_context->info.USER_AGENT);
                        json_object_dotset_string(root_object, "d.properties.$device", yadl_context->info.APPLICATION);
                        json_object_dotset_string(root_object, "d.status", "dnd");
                        json_object_dotset_boolean(root_object, "d.afk", false);
                        json_object_dotset_value(root_object, "d.presence.activities",
                                                 json_parse_string("[{\"name\": \"Testing\", \"type\": 1}]"));
                        json_object_dotset_number(root_object, "d.intents", yadl_context->info.GATEWAY_INTENTS);
                        yadl_json_lws_write(wsi, root_object);
                    }
                    break;
                }
                default:
                    break;
            }
            break;
        }

        case LWS_CALLBACK_CLIENT_ESTABLISHED:
            lwsl_user("WS %s%s 101\n", ws_payload->address, ws_payload->path);
            ws_payload->retry_count = 0;
            break;

        case LWS_CALLBACK_WS_PEER_INITIATED_CLOSE: {
            int16_t code;
            char *close_reason = yadl_malloc(len - 2);

            memcpy(&code, in, 0x2);
            memcpy(close_reason, in + 0x2, len - 0x2);

            lwsl_err("Server disconnected websocket connection. (%d) - %s", ntohs(code), close_reason);
            switch (ntohs(code)) {
                case 4004:
                    ws_payload->connection_exhausted = true;
                    break;

                default:
                    break;
            }
            break;
        }

        case LWS_CALLBACK_CLIENT_CLOSED:
            if (!ws_payload->connection_exhausted) {
                lwsl_err("Client disconnected websocket connection. trying to reconnect..");
                connection_retry(wsi, &ws_payload->sul, schedule_callback, &ws_payload->retry_count);
            } else
                return -1;
            break;

        default:
            break;
    }

    return 0;
}

static const struct lws_protocols protocols[] = {
        {"websocket", main_websocket_callback, 0, 0, 0, NULL, 0},
        LWS_PROTOCOL_LIST_TERM
};

int start_main_client(yadl_context_t *yadl_context) {
    yadl_pthread_append(pthread_self());
    struct http_result *http_result = http_request("GET", (char *) YADL_RETRIEVE_GATEWAY_URL, NULL, NULL,
                                                   (char *) YADL_USER_AGENT, NULL);

    if (!strlen(*http_result->response_body)) {
        lwsl_err("Can't retrieve discord gateway address. check your internet connection.");
        return EXIT_FAILURE;
    }

    const char *URL = yadl_strcat(
            json_object_dotget_string(json_object(json_parse_string(*http_result->response_body)), "url"),
            yadl_context->info.GATEWAY_PATH);

    struct main_client_payload *main_payload = yadl_malloc(sizeof(struct main_client_payload));
    *main_payload = (struct main_client_payload) {yadl_context, NULL,};

    struct lws_context_creation_info info;
    memset(&info, 0, sizeof info);

    info.options = LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT;
    info.port = CONTEXT_PORT_NO_LISTEN; /* we do not run any server */
    info.protocols = protocols;
    info.user = main_payload;
    info.pt_serv_buf_size = YADL_LARGE_SIZE * 1000;

    info.fd_limit_per_thread = 3;

    main_payload->context = lws_create_context(&info);
    if (!main_payload->context) {
        lwsl_err("lws init failed..");
        return 1;
    }

    main_payload->address = yadl_malloc(strlen(URL));
    main_payload->path = yadl_malloc(strlen(URL));
    sscanf(URL, "wss://%99[^/]/%199[^\n]", main_payload->address, main_payload->path);

    /* schedule the first client connection attempt to happen immediately */
    lws_sul_schedule(main_payload->context, 0x0, &main_payload->sul, schedule_callback, 1);

    int n = 0;
    while (!main_payload->connection_exhausted && n >= 0)
        n = lws_service(main_payload->context, 0);

    lws_context_destroy(main_payload->context);
    main_payload->client_wsi = NULL;
    yadl_gc_set_alive(false);

    pthread_join(*((yadl_pthread_context_t *) ((gc_node_t *) yadl_gc_get_context(
            YADL_GC_NODE_PTHREAD))->address)->pthread, NULL);
    return 0;
}
