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

#ifndef YADL_VOICE_UDP_CLIENT_H
#define YADL_VOICE_UDP_CLIENT_H

#include <libwebsockets.h>
#include <math.h>
#include <opus/opus.h>
#include <sodium.h>
#include <string.h>
#include <signal.h>
#include <sys/un.h>
#include <sys/fcntl.h>
#include <sys/stat.h>
#include <parson.h>
#if !defined(WIN32)
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#endif
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#if !defined(WIN32)
#include <unistd.h>
#endif
#include <errno.h>
#include <stdbool.h>

#include "../utils/utils.h"
#include "../json/json.h"
#include "../impl/linked_list.h"
#include "../websockets/voice_client.h"

#define YADL_VOICE_UDP_CLIENT_OPUS_SAMPLE_RATE 48000
#define YADL_VOICE_UDP_CLIENT_OPUS_BPS 16
#define YADL_VOICE_UDP_CLIENT_OPUS_CHANNELS 2
#define YADL_VOICE_UDP_CLIENT_OPUS_FRAME_SIZE 960

typedef struct {
    u_int16_t sequence;
    u_int32_t timestamp;
    OpusEncoder *opus_encoder;
    bool speak;

    struct timespec start_time;
} voice_udp_client_object_t;

typedef struct {
    bool *alive;
    struct lws *voice_udp_client_wsi;
    struct lws *voice_client_wsi;
    char* address;
    u_int16_t port;
    u_int32_t ssrc;
    unsigned char secret_key[32];
    voice_udp_client_object_t *client_object;
} voice_udp_client_payload_t;

int start_voice_udp_client(voice_udp_client_payload_t *payload);

#endif //YADL_VOICE_UDP_CLIENT_H
