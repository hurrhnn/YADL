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

#ifndef YADL_VOICE_CLIENT_H
#define YADL_VOICE_CLIENT_H

#include <arpa/inet.h>
#include "../yadl.h"
#include "../raw/voice_udp_client.h"

void yadl_init_voice_client(yadl_context_t *context, channel_t *voice_channel);

typedef struct {
    size_t *heartbeat, *sequence;

    pthread_t *heartbeat_voice;
    pthread_cond_t *voice_client_cond, *voice_heartbeat_cond;
    pthread_mutex_t *voice_client_mutex, *voice_heartbeat_mutex;

    bool invalid_session;
    int64_t *heartbeat_interval;

    u_int16_t udp_port;
    u_int32_t ssrc;
} voice_client_object_t;

typedef struct {
    yadl_context_t *yadl_context;
    struct lws *client_wsi;
    struct lws_context *context;

    char *address;
    char *path;
    lws_sorted_usec_list_t sul;
    uint16_t retry_count;

    bool connection_exhausted;

    const char* server_id;
    const char* user_id;
    const char* session_id;
    const char* token;

    voice_client_object_t *client_object;
} voice_client_payload_t;

int start_voice_client(voice_client_payload_t *payload);

#endif //YADL_VOICE_CLIENT_H
