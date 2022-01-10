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

#ifndef YADL_VOICE_H
#define YADL_VOICE_H

#include <stdbool.h>
#include "parson.h"
#include "../utils/utils.h"

typedef struct yadl_voice_state {
    char *guild_id;
    char *channel_id;
    char *user_id;
    char *member;
    /* guild member object */
    char *session_id;
    bool deaf;
    bool mute;
    bool self_deaf;
    bool self_mute;
    bool self_stream;
    bool self_video;
    bool suppress;
    char *request_to_speak_timestamp;

} voice_state_t;

typedef struct yadl_voice_region {
    char *id;
    char *name;
    bool optimal;
    bool deprecated;
    bool custom;

} voice_region_t;

voice_state_t *parse_voice_state(JSON_Value *voice_state_value);

voice_region_t *parse_voice_region(JSON_Value *voice_region_value);

#endif //YADL_VOICE_H
