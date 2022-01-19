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

#include "voice_client.h"

void yadl_init_voice_client(yadl_context_t *context, channel_t *voice_channel) {
    JSON_Object *voice_state_update = yadl_json_object_builder(NULL);
    json_object_dotset_number(voice_state_update, "op", 4);
    json_object_dotset_string(voice_state_update, "d.channel_id", voice_channel->id);
    json_object_dotset_string(voice_state_update, "d.guild_id", voice_channel->guild_id);
    json_object_dotset_boolean(voice_state_update, "d.self_mute", false);
    json_object_dotset_boolean(voice_state_update, "d.self_deaf", false);
    yadl_json_lws_write(context->main_wsi, voice_state_update);
}

static const u_int32_t backoff_ms[] = { 1000, 2000, 3000, 4000, 5000 };

static const lws_retry_bo_t retry = {
        .retry_ms_table            = backoff_ms,
        .retry_ms_table_count        = LWS_ARRAY_SIZE(backoff_ms),
        .conceal_count            = LWS_ARRAY_SIZE(backoff_ms),

        .secs_since_valid_ping        = 3,  /* force PINGs after secs idle */
        .secs_since_valid_hangup    = 10, /* hangup after secs idle */

        .jitter_percent            = 20,
};

void voice_websocket_connection_retry(struct lws *client_wsi, lws_sorted_usec_list_t *sul, sul_cb_t callback, u_int16_t *retry_count) {
    if (lws_retry_sul_schedule_retry_wsi(client_wsi, sul, callback, retry_count)) {
        lwsl_err("connection attempts exhausted.\n");
        ((voice_client_payload_t *) lws_context_user(lws_get_context(client_wsi)))->connection_exhausted = true;
    }
}

void voice_websocket_schedule_callback(lws_sorted_usec_list_t *sul) {
    yadl_pthread_append(pthread_self());
    voice_client_payload_t *voice_payload = lws_container_of(sul, voice_client_payload_t, sul);
    struct lws_client_connect_info i;
    memset(&i, 0, sizeof(i));

    i.context = voice_payload->context;
    i.port = 443;
    i.address = voice_payload->address;
    i.path = voice_payload->path;
    i.host = i.address;
    i.ssl_connection = LCCSCF_USE_SSL;
    i.pwsi = &voice_payload->client_wsi;
    i.retry_and_idle_policy = &retry;
    i.userdata = voice_payload;

    if (!lws_client_connect_via_info(&i))
        lws_retry_sul_schedule(voice_payload->context, 0, sul, &retry, voice_websocket_schedule_callback,
                               &voice_payload->retry_count);
}

void voice_websocket_object_init(voice_client_payload_t *payload) {
    if (payload->client_object == NULL) {
        payload->client_object = yadl_malloc(sizeof(voice_client_object_t), true);
        *payload->client_object = (voice_client_object_t) {yadl_malloc(sizeof(size_t), true),
                                                                           yadl_malloc(sizeof(size_t), true), NULL,
                                                                           yadl_malloc(sizeof(pthread_cond_t), true), NULL,
                                                                           yadl_malloc(sizeof(pthread_mutex_t), true), NULL,
                                                                           true,
                                                                           yadl_malloc(YADL_MAIN_SESSION_ID_LENGTH, true),
                                                                           0};

        pthread_cond_init(payload->client_object->voice_client_cond, NULL);
        pthread_mutex_init(payload->client_object->voice_client_mutex, NULL);
    }
}

void voice_websocket_wait_signal(pthread_mutex_t *pthread_mutex, pthread_cond_t *pthread_cond, struct timespec *timespec) {
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

void *voice_websocket_send_heartbeat(voice_client_payload_t *ws_payload) {
    struct timeval tv;
    struct timespec ts;
    while (!ws_payload->connection_exhausted) {
        JSON_Object *root_object = yadl_json_object_builder(NULL);
        json_object_dotset_number(root_object, "op", 3);
        json_object_dotset_number(root_object, "d", (double) (*ws_payload->client_object->heartbeat += 1));

        yadl_json_lws_write(ws_payload->client_wsi, root_object);

        gettimeofday(&tv, NULL);
        long future_us = tv.tv_usec + *ws_payload->client_object->heartbeat_interval * 1000;
        ts.tv_nsec = (future_us % 1000000) * 1000;
        ts.tv_sec = tv.tv_sec + future_us / 1000000;

        pthread_cond_signal(ws_payload->client_object->voice_client_cond);
        voice_websocket_wait_signal(ws_payload->client_object->voice_heartbeat_mutex,
                                   ws_payload->client_object->voice_heartbeat_cond, &ts);
    }
    return NULL;
}

int voice_websocket_callback(struct lws *wsi, enum lws_callback_reasons reason,
                            __attribute__((unused)) void *user, void *in, size_t len) {
    yadl_pthread_append(pthread_self());
    voice_client_payload_t *ws_payload = lws_context_user(lws_get_context((wsi)));
    ws_payload->client_wsi = wsi;

    switch (reason) {
        case LWS_CALLBACK_WSI_CREATE: {
            voice_websocket_object_init(ws_payload);
            break;
        }

        case LWS_CALLBACK_CLIENT_CONNECTION_ERROR: {
            lwsl_err("CLIENT_CONNECTION_ERROR: %s\n",
                     in ? (char *) in : "(null)");
            voice_websocket_connection_retry(wsi, &ws_payload->sul, voice_websocket_schedule_callback,
                                            &ws_payload->retry_count);
            break;
        }

        case LWS_CALLBACK_CLIENT_RECEIVE: {
            char *raw = json_serialize_to_string_pretty(json_parse_string(in));
            if (raw == NULL)
                break;

            JSON_Object *root_object = yadl_json_object_builder(raw);
            *ws_payload->client_object->sequence = (size_t) (json_object_dotget_number(root_object, "s") == 0
                                                             ? (double) *ws_payload->client_object->sequence
                                                             : json_object_dotget_number(root_object, "s"));
            u_int8_t op_code = (u_int8_t) json_object_dotget_number(root_object, "op");
            JSON_Object *data_object = json_object_dotget_object(root_object, "d");

            switch (op_code) {
                case 0: {
                    break;
                }

                case 2: {
                    union {
                        struct {
                            int16_t type;
                            int16_t length;
                            u_int32_t ssrc;
                            unsigned char address[0x40];
                            int16_t port;
                        } data;
                        unsigned char combined_data[0x4a];
                    } ip_discovery_packet;

                    ip_discovery_packet.data.type = (int16_t) yadl_swap_endian_uint16(0x1);
                    ip_discovery_packet.data.length = (int16_t) yadl_swap_endian_uint16(0x46);
                    ip_discovery_packet.data.ssrc = yadl_swap_endian_uint32((u_int32_t) json_object_dotget_number(data_object, "ssrc"));
                    memset(ip_discovery_packet.data.address, 0x0, 0x40);
                    strcpy((char *) ip_discovery_packet.data.address, json_object_dotget_string(data_object, "ip"));
                    ip_discovery_packet.data.port = (int16_t) yadl_swap_endian_uint16((int16_t) json_object_dotget_number(data_object, "port"));

                    int sock_fd;
                    char buffer[0x4a + 1];
                    struct sockaddr_in server_address;

                    if ((sock_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
                        lwsl_err("[IP DISCOVERY] Error: socket creation failed.");
                        exit(EXIT_FAILURE);
                    }

                    memset(&server_address, 0, sizeof(server_address));
                    server_address.sin_family = AF_INET;
                    server_address.sin_port = ip_discovery_packet.data.port;

                    struct hostent *hostent;
                    struct in_addr **address_list;

                    if ((hostent = gethostbyname((const char *)ip_discovery_packet.data.address)) == NULL) {
                        lwsl_err("[IP DISCOVERY] Error: Connection Cannot resolved to %s.\n", (const char *)ip_discovery_packet.data.address);
                        ws_payload->connection_exhausted = true;
                        return -1;
                    } else {
                        address_list = (struct in_addr **) hostent->h_addr_list;
                        strcpy((char *)ip_discovery_packet.data.address, inet_ntoa(*address_list[0]));
                    }

                    if (!inet_pton(AF_INET, (char *)ip_discovery_packet.data.address, &server_address.sin_addr)) {
                        lwsl_err("[IP DISCOVERY] Error: Convert Internet host address Failed.");
                        ws_payload->connection_exhausted = true;
                        return -1;
                    }

                    size_t size;
                    sendto(sock_fd, (const char *) ip_discovery_packet.combined_data, 0x4a, 0,
                           (const struct sockaddr *) &server_address,sizeof(server_address));

                    size = recvfrom(sock_fd, (char *) buffer, 0x4a, 0, NULL, NULL);
                    memcpy(ip_discovery_packet.combined_data, buffer, size);
                    close(sock_fd);

                    ws_payload->client_object->udp_port = yadl_swap_endian_uint16(ip_discovery_packet.data.port);
                    ws_payload->client_object->ssrc = yadl_swap_endian_uint32(ip_discovery_packet.data.ssrc);

                    /* An debug stuff, change the below text_channel id if you want. */
                    char* content = yadl_malloc(YADL_MIDIUM_SIZE);
                    sprintf(content, "IP Discovered Address: `%s:%d`, SSRC: %d", ip_discovery_packet.data.address, ws_payload->client_object->udp_port, ws_payload->client_object->ssrc);
                    yadl_create_message(ws_payload->yadl_context, "930011355644305428", content, false, NULL, NULL, NULL, NULL, NULL); // An debug stuff

                    JSON_Object *select_protocol_json = yadl_json_object_builder(NULL);
                    json_object_dotset_number(select_protocol_json, "op", 1);
                    json_object_dotset_string(select_protocol_json, "d.protocol", "udp");
                    json_object_dotset_string(select_protocol_json, "d.data.address", (const char *) ip_discovery_packet.data.address);
                    json_object_dotset_number(select_protocol_json, "d.data.port", ws_payload->client_object->udp_port);
                    json_object_dotset_string(select_protocol_json, "d.data.mode", "xsalsa20_poly1305");

                    yadl_json_lws_write(wsi, select_protocol_json);
                    break;
                }

                case 4: {
                    voice_udp_client_payload_t *voice_udp_payload = yadl_malloc(sizeof(voice_udp_client_payload_t));
                    voice_udp_payload->voice_websocket_wsi = wsi;
                    voice_udp_payload->port = ws_payload->client_object->udp_port;
                    voice_udp_payload->ssrc = ws_payload->client_object->ssrc;
                    for(int i = 0; i < json_array_get_count(json_object_dotget_array(data_object, "secret_key")); i++)
                        voice_udp_payload->secret_key[i] = (unsigned char )json_array_get_number(json_object_dotget_array(data_object, "secret_key"), i);
                    yadl_pthread_create(start_voice_udp_client, NULL, voice_udp_payload);
                    break;
                }

                case 8: {
                    *ws_payload->client_object->heartbeat_interval = (int64_t) json_object_dotget_number(root_object,
                                                                                                         "d.heartbeat_interval");
                    if(!ws_payload->client_object->invalid_session) {
                        root_object = yadl_json_object_builder(NULL);
                        json_object_dotset_number(root_object, "op", 7);
                        json_object_dotset_string(root_object, "d.server_id", ws_payload->server_id);
                        json_object_dotset_string(root_object, "d.token", ws_payload->token);
                        json_object_dotset_string(root_object, "d.session_id", ws_payload->session_id);
                        yadl_json_lws_write(wsi, root_object);
                    } else {
                        ws_payload->client_object->invalid_session = false;
                        root_object = yadl_json_object_builder(NULL);
                        json_object_dotset_number(root_object, "op", 0);
                        json_object_dotset_string(root_object, "d.server_id", ws_payload->server_id);
                        json_object_dotset_string(root_object, "d.user_id", ws_payload->user_id);
                        json_object_dotset_string(root_object, "d.session_id", ws_payload->session_id);
                        json_object_dotset_string(root_object, "d.token", ws_payload->token);
                        yadl_json_lws_write(wsi, root_object);
                    }

                    if (ws_payload->client_object->heartbeat_voice == NULL) {
                        yadl_pthread_context_t *heartbeat_main_context = yadl_pthread_create(
                                voice_websocket_send_heartbeat,
                                NULL, ws_payload);

                        ws_payload->client_object->heartbeat_voice = heartbeat_main_context->pthread;
                        ws_payload->client_object->voice_heartbeat_cond = heartbeat_main_context->pthread_cond;
                        ws_payload->client_object->voice_heartbeat_mutex = heartbeat_main_context->pthread_mutex;
                        lwsl_user("op %d, Started voice heartbeat thread..", op_code);

                        voice_websocket_wait_signal(ws_payload->client_object->voice_client_mutex,
                                                    ws_payload->client_object->voice_client_cond, NULL);

                        /* An debug stuff, change the below text_channel id if you want. */
                        char* content = yadl_malloc(YADL_MIDIUM_SIZE);
                        sprintf(content, "Successfully Connected & Identified!");
                        yadl_create_message(ws_payload->yadl_context, "930011355644305428", content, false, NULL, NULL, NULL, NULL, NULL);
                    } else {
                        pthread_cond_signal(ws_payload->client_object->voice_heartbeat_cond);
                        lwsl_user("op %d, Sent signal to exist heartbeat thread..", op_code);

                        voice_websocket_wait_signal(ws_payload->client_object->voice_client_mutex,
                                                    ws_payload->client_object->voice_client_cond, NULL);
                    }
                    break;
                }

                case 13: {
                    ws_payload->connection_exhausted = true;
                    return -1;
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
            char *close_reason = yadl_malloc(len - 1);

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
                voice_websocket_connection_retry(wsi, &ws_payload->sul, voice_websocket_schedule_callback,
                                                &ws_payload->retry_count);
            } else
                return -1;
            break;

        default:
            break;
    }

    return 0;
}

static const struct lws_protocols protocols[] = {
        {"voice-websocket", voice_websocket_callback, 0, 0, 0, NULL, 0},
        LWS_PROTOCOL_LIST_TERM
};

int start_voice_client(voice_client_payload_t *payload) {
    struct lws_context_creation_info info;
    memset(&info, 0, sizeof info);

    info.options = LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT;
    info.port = CONTEXT_PORT_NO_LISTEN; /* we do not run any server */
    info.protocols = protocols;

    info.user = payload;
    info.pt_serv_buf_size = YADL_LARGE_SIZE * 1000;

    info.fd_limit_per_thread = 3;

    payload->context = lws_create_context(&info);
    if (!payload->context) {
        lwsl_err("lws init failed..");
        return 1;
    }

    /* schedule the first client connection attempt to happen immediately */
    lws_sul_schedule(payload->context, 0x0, &payload->sul, voice_websocket_schedule_callback, 1);

    int n = 0;
    while (!payload->connection_exhausted && n >= 0)
        n = lws_service(payload->context, 0);

    lws_context_destroy(payload->context);
    payload->client_wsi = NULL;
    return 0;
}
