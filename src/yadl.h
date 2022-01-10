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

#include "utils/info.h"
#include "utils/utils.h"
#include "api/api.h"
#include "impl/impl.h"

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
