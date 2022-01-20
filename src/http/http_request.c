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

#include "http_request.h"

const lws_retry_bo_t http_retry = {
        .secs_since_valid_ping = 3,
        .secs_since_valid_hangup = 10,
};

int callback_http(struct lws *wsi, enum lws_callback_reasons reason,
                  void *user, void *in, size_t len) {
    yadl_pthread_append(pthread_self());
    http_payload_t *http_payload = lws_context_user(lws_get_context((wsi)));
    switch (reason) {
        case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
            lwsl_err("[%s] Client connection error. - %s",
                     in ? (char *) in : "(null)", lws_get_protocol(wsi)->name);
            *http_payload->response_code = 0;
            http_payload->status = true;
            lws_cancel_service(lws_get_context(wsi));
            break;

        case LWS_CALLBACK_ESTABLISHED_CLIENT_HTTP: {
            char buf[YADL_MIDIUM_SIZE];
            lws_get_peer_simple(wsi, buf, sizeof(buf));
            *http_payload->response_code = lws_http_client_http_response(wsi);
            http_payload->data_ready = true;
            break;
        }

        case LWS_CALLBACK_CLIENT_APPEND_HANDSHAKE_HEADER: {
            unsigned char **p = (unsigned char **) in, *end = (*p) + len;
            if (lws_add_http_header_by_token(wsi, WSI_TOKEN_HTTP_USER_AGENT,
                                             (unsigned char *) http_payload->user_agent,
                                             (int) strlen(http_payload->user_agent), p, end)) {
                *http_payload->response_code = 0;
                return -1;
            }

            if (lws_add_http_header_by_token(wsi, WSI_TOKEN_HTTP_ACCEPT,
                                             (unsigned char *) "*/*", (int) strlen("*/*"), p, end))
                return -1;

            if (http_payload->cookie_len > 0) {
                if (lws_add_http_header_by_token(wsi, WSI_TOKEN_HTTP_COOKIE,
                                                 (const unsigned char *) http_payload->cookie,
                                                 (int) http_payload->cookie_len, p, end)) {
                    *http_payload->response_code = 0;
                    return -1;
                }
            }

            bool is_set_content_type = false;
            if (http_payload->header_len > 0) {
                char *headers = strtok(http_payload->header, "\n");
                while (headers != NULL) {
                    char *authorization_pos = strstr(headers, "Authorization: ");
                    char *content_type_pos = strstr(headers, "Content-Type: ");

                    if (authorization_pos != NULL) {
                        size_t offset = strlen("Authorization: ");
                        size_t auth_len = strlen(authorization_pos + offset);
                        if (lws_add_http_header_by_token(wsi, WSI_TOKEN_HTTP_AUTHORIZATION,
                                                         (const unsigned char *) authorization_pos + offset,
                                                         (int) auth_len, p, end)) {
                            *http_payload->response_code = 0;
                            return -1;
                        }

                    } else if (content_type_pos != NULL) {
                        size_t offset = strlen("Content-Type: ");
                        size_t c_type_len = strlen(content_type_pos + offset);
                        if (lws_add_http_header_by_token(wsi, WSI_TOKEN_HTTP_CONTENT_TYPE,
                                                         (const unsigned char *) content_type_pos + offset,
                                                         (int) c_type_len, p, end)) {
                            *http_payload->response_code = 0;
                            return -1;
                        }
                        is_set_content_type = true;
                    }
                    headers = strtok(NULL, "\n");
                }
            }

            if(!is_set_content_type) {
                char content_type[] = "application/json; charset=utf-8";
                if (lws_add_http_header_by_token(wsi, WSI_TOKEN_HTTP_CONTENT_TYPE,
                                                 (unsigned char *) content_type,
                                                 (int) strlen(content_type), p, end)) {
                    *http_payload->response_code = 0;
                    return -1;
                }
            }

            if (http_payload->request_body_len > 0) {
                char *body_len_str = yadl_malloc(YADL_SMALL_SIZE);
                snprintf(body_len_str, YADL_SMALL_SIZE, "%zu", http_payload->request_body_len);
                if (lws_add_http_header_by_token(wsi, WSI_TOKEN_HTTP_CONTENT_LENGTH,
                                                 (unsigned char *) body_len_str,
                                                 (int) strlen(body_len_str), p, end)) {
                    *http_payload->response_code = 0;
                    return -1;
                }

                lws_client_http_body_pending(wsi, 1);
                lws_callback_on_writable(wsi);
            }
            break;
        }

        case LWS_CALLBACK_CLIENT_HTTP_WRITEABLE: {
            lws_write_http(wsi, *http_payload->request_body, http_payload->request_body_len);
            lws_client_http_body_pending(wsi, 0);
            break;
        }

        case LWS_CALLBACK_RECEIVE_CLIENT_HTTP_READ: {
            if (http_payload->data_ready) {
                lwsl_header("RECEIVE_CLIENT_HTTP_READ: read %d\n", (int) len);
                size_t before_data_len = http_payload->response_body_len;
                http_payload->response_body_len += len;

                if (http_payload->response_body_len >= http_payload->current_response_len) {
                    http_payload->current_response_len += YADL_LARGE_SIZE;
                    *http_payload->response_body = yadl_realloc(*http_payload->response_body,
                                                                http_payload->current_response_len);
                }
                memcpy(*http_payload->response_body + before_data_len, in, len);
                break;
            }
        }

        case LWS_CALLBACK_RECEIVE_CLIENT_HTTP: {
            char buffer[YADL_LARGE_SIZE + LWS_PRE];
            char *px = buffer + LWS_PRE;
            int p_len = sizeof(buffer) - LWS_PRE;
            lws_http_client_read(wsi, &px, &p_len);
            break;
        }

        case LWS_CALLBACK_COMPLETED_CLIENT_HTTP:
        case LWS_CALLBACK_CLOSED_CLIENT_HTTP:
            http_payload->status = true;
            lws_cancel_service(lws_get_context(wsi)); /* abort poll wait */
            break;

        default:
            break;
    }

    return lws_callback_http_dummy(wsi, reason, user, in, len);
}

const struct lws_protocols protocols[] = {
        {
                "http",
                callback_http,
                sizeof(http_payload_t), 0, 0, NULL, 0
        },
        LWS_PROTOCOL_LIST_TERM
};

int notify_callback(lws_state_manager_t *mgr, __attribute__((unused)) lws_state_notify_link_t *link,
                    int current, int target) {
    yadl_pthread_append(pthread_self());
    struct lws_context *context = mgr->parent;
    struct lws_client_connect_info i;

    if (current != LWS_SYSTATE_OPERATIONAL || target != LWS_SYSTATE_OPERATIONAL)
        return 0;

    memset(&i, 0, sizeof i);
    i.context = context;
    i.ssl_connection = LCCSCF_USE_SSL;
    i.port = 443;
    i.address = ((http_payload_t *) (lws_context_user(context)))->address;

    i.ssl_connection |= LCCSCF_H2_QUIRK_OVERFLOWS_TXCR |
                        LCCSCF_ACCEPT_TLS_DOWNGRADE_REDIRECTS |
                        LCCSCF_H2_QUIRK_NGHTTP2_END_STREAM |
                        LCCSCF_IP_LOW_LATENCY |
                        LCCSCF_IP_HIGH_THROUGHPUT;

    i.alpn = "http/1.1";
    i.ssl_connection |= LCCSCF_SKIP_SERVER_CERT_HOSTNAME_CHECK;
    i.retry_and_idle_policy = &http_retry;
    i.path = ((http_payload_t *) (lws_context_user(context)))->path;

    i.host = i.address;
    i.origin = i.address;
    i.method = ((http_payload_t *) (lws_context_user(context)))->method;

    i.protocol = protocols[0].name;
    i.pwsi = &((http_payload_t *) (lws_context_user(context)))->client_wsi;

    if (!lws_client_connect_via_info(&i)) {
        lwsl_err("[%s] HTTP Request creation failed..\n", protocols->name);
        *((http_payload_t *) (lws_context_user(context)))->response_code = 0;
        ((http_payload_t *) (lws_context_user(context)))->status = 1;
        lws_cancel_service(context);
        return -1;
    }
    return 0;
}

http_result_t *
http_request(const char *method, const char *URL, char *header, char *cookie, const char *user_agent, char **request_body, size_t request_body_size) {
    yadl_pthread_append(pthread_self());

    struct lws_context *context;
    struct lws_context_creation_info info;
    struct lws *client_wsi = yadl_malloc(sizeof(void *));

    lws_state_notify_link_t notifier = {{NULL, NULL, NULL}, notify_callback, ""};
    lws_state_notify_link_t *na[] = {&notifier, NULL};

    http_payload_t *http_payload = yadl_malloc(sizeof(http_payload_t));
    http_result_t *http_result = yadl_malloc(sizeof(http_result_t));

    memset(&info, 0, sizeof info);
    memset(http_payload, 0, sizeof(http_payload_t));

    char **response_body = yadl_malloc(sizeof(void *));
    *response_body = yadl_malloc(YADL_LARGE_SIZE, true);

    http_result->response_body = response_body;
    http_result->response_code = -1;

    http_payload->address = yadl_malloc(strlen(URL));
    http_payload->path = yadl_malloc(strlen(URL));
    sscanf(URL, "https://%99[^/]/%199[^\n]", http_payload->address, http_payload->path);

    http_payload->method = method;
    http_payload->header = header;
    http_payload->cookie = cookie;
    http_payload->user_agent = (char *) user_agent;

    http_payload->client_wsi = client_wsi;
    http_payload->status = false;
    http_payload->data_ready = false;
    http_payload->request_body = request_body;
    http_payload->request_body_len = http_payload->request_body == NULL ? 0 : request_body_size;
    http_payload->response_body = http_result->response_body;
    http_payload->response_body_len = 0;
    http_payload->current_response_len = YADL_LARGE_SIZE;
    http_payload->response_code = &http_result->response_code;

    http_payload->header_len = http_payload->header == NULL ? 0 : strlen(http_payload->header);
    http_payload->cookie_len = http_payload->cookie == NULL ? 0 : strlen(http_payload->cookie);

    info.timeout_secs = 10;
    info.connect_timeout_secs = 10;
    info.options = LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT |
                   LWS_SERVER_OPTION_H2_JUST_FIX_WINDOW_UPDATE_OVERFLOW;
    info.port = CONTEXT_PORT_NO_LISTEN;

    info.protocols = protocols;
    info.register_notifier_list = na;

    info.user = http_payload;
    info.pt_serv_buf_size = http_payload->request_body_len + (YADL_LARGE_SIZE * 2);

    info.fd_limit_per_thread = 3;
    context = lws_create_context(&info);

    if (!context) {
        lwsl_err("[%s] lws init failed..", protocols->name);
        return NULL;
    }

    int n = 0;
    while (n >= 0 && !http_payload->status)
        n = lws_service(context, 0);

    http_result->response_size = http_payload->current_response_len;
    lwsl_header("%s %s/%s %u\n", http_payload->method, http_payload->address, http_payload->path, *http_payload->response_code);
    lwsl_hexdump_level(LLL_HEADER, *http_payload->response_body, http_payload->response_body_len);

    if(*http_payload->response_code / 100 != 2)
        lwsl_warn("[%s] %s %s/%s %u, \n%s", protocols->name, http_payload->method, http_payload->address, http_payload->path, *http_payload->response_code, *http_payload->response_body);

    lws_context_destroy(context);
    return http_result;
}
