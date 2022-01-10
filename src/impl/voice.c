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

#include "voice.h"

voice_state_t *parse_voice_state(JSON_Value *voice_state_value) {
    JSON_Object *voice_state = json_object(voice_state_value);
    voice_state_t *result = yadl_malloc(sizeof(voice_state_t));

    *result = (voice_state_t) {(char *) json_object_get_string(voice_state, "guild_id"),
                               (char *) json_object_get_string(voice_state, "channel_id"),
                               (char *) json_object_get_string(voice_state, "user_id"),
                               (char *) json_serialize_to_string(json_object_get_wrapping_value(json_object_get_object(voice_state, "member"))),
                               (char *) json_object_get_string(voice_state, "session_id"),
                               json_object_get_boolean(voice_state, "deaf"),
                               json_object_get_boolean(voice_state, "mute"),
                               json_object_get_boolean(voice_state, "self_deaf"),
                               json_object_get_boolean(voice_state, "self_mute"),
                               json_object_get_boolean(voice_state, "self_stream"),
                               json_object_get_boolean(voice_state, "self_video"),
                               json_object_get_boolean(voice_state, "suppress"),
                               (char *) json_object_get_string(voice_state, "request_to_speak_timestamp")
    };

    return result;
}

voice_region_t *parse_voice_region(JSON_Value *voice_region_value) {
    JSON_Object *voice_region = json_object(voice_region_value);
    voice_region_t *result = yadl_malloc(sizeof(voice_region_t));

    *result = (voice_region_t) {(char *) json_object_get_string(voice_region, "id"),
                                (char *) json_object_get_string(voice_region, "name"),
                                json_object_get_boolean(voice_region, "optimal"),
                                json_object_get_boolean(voice_region, "deprecated"),
                                json_object_get_boolean(voice_region, "custom")
    };

    return result;
}
