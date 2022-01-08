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

#include <libwebsockets.h>
#include <stdbool.h>

#include "../../impl/impl.h"
#include "../../yadl.h"

#ifndef YADL_MAIN_CLIENT_H
#define YADL_MAIN_CLIENT_H

#define YADL_MAIN_SESSION_ID_LENGTH (0x20 + 0x1) // 0x1 indicates null termination.


int start_main_client(yadl_context_t *URL);

struct main_client_object {
    size_t *heartbeat, *sequence;

    pthread_t *heartbeat_main;
    pthread_cond_t *main_client_cond, *main_heartbeat_cond;
    pthread_mutex_t *main_client_mutex, *main_heartbeat_mutex;

    bool invalid_session;
    int64_t *heartbeat_interval;
    self_user_t *self_user;
    char *test;
    char *session_id;
};

struct main_client_payload {
    yadl_context_t *yadl_context;
    struct lws *client_wsi;
    struct lws_context *context;

    char *address;
    char *path;
    lws_sorted_usec_list_t sul;
    uint16_t retry_count;
    bool connection_exhausted;

    struct main_client_object *client_object;
};

#endif //YADL_MAIN_CLIENT_H
