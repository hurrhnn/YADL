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

#ifndef YADL_H
#define YADL_H

#include <libwebsockets.h>
#include <strings.h>
#include <stdlib.h>

#include "utils/utils.h"
#include "impl/impl.h"

#define YADL_MAJOR_VERSION "0"
#define YADL_MINOR_VERSION "0"
#define YADL_REVISION "3"
#define YADL_VERSION (YADL_MAJOR_VERSION "." YADL_MINOR_VERSION "." YADL_REVISION)

#define YADL_DEFAULT_API_VER 9
#define YADL_DEFAULT_GATEWAY_VER 9
#define YADL_DEFAULT_VOICE_VER 4

#define YADL_APPLICATION "YADL"
#define YADL_USER_AGENT "Mozilla/5.0 (X11; Fedora; Linux x86_64; rv:91.0) Gecko/20100101 Firefox/91.0"
#define YADL_AUTHORIZATION_HEADER "Authorization: Bot %s"

#define YADL_RETRIEVE_GATEWAY_URL "https://discord.com/api/gateway"
#define YADL_API_URL "https://discord.com/api/v%d"

#define YADL_CDN_URL "https://cdn.discordapp.com"
#define YADL_USER_AVATAR "/avatars/%s/%s.png"

#define YADL_GATEWAY_PATH "/?v=%d&encoding=json"
#define YADL_VOICE_PATH "/?v=%d"
#define YADL_CREATE_MESSAGE_PATH "/channels/%s/messages"

#define YADL_SET_VALUE_IF_NULL(var, value) var = ((var) == 0 ? (var) = (value) : (var))

typedef struct yadl_context_info {
    int     API_VER, GATEWAY_VER, VOICE_VER,
            GATEWAY_INTENTS;

    char    APPLICATION[YADL_MIDIUM_SIZE],
            USER_AGENT[YADL_MIDIUM_SIZE],
            TOKEN[YADL_MIDIUM_SIZE],
            AUTHORIZATION_HEADER[YADL_MIDIUM_SIZE],

            API_URL[YADL_MIDIUM_SIZE],
            GATEWAY_PATH[YADL_MIDIUM_SIZE],
            VOICE_PATH[YADL_MIDIUM_SIZE];

} yadl_context_info_t;

typedef struct yadl_context {
    yadl_context_info_t info;
    yadl_event_cb_t callbacks;
    obj_list_t *guilds;
} yadl_context_t;

void yadl_init(yadl_context_t *yadl_context);

void yadl_launch(yadl_context_t *yadl_context);

void yadl_cleanup();

#endif
