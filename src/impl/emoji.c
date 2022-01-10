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

#include "emoji.h"
#include "parson.h"
#include "../utils/utils.h"

emoji_t *parse_emoji(JSON_Value *emoji_value) {
    JSON_Object *emoji = json_object(emoji_value);
    emoji_t *result = yadl_malloc(sizeof(emoji_t), true);

    *result = (emoji_t) {(char *) json_object_get_string(emoji, "id"),
                         (char *) json_object_get_string(emoji, "name"),
                         (char *) json_serialize_to_string(json_array_get_wrapping_value(json_object_get_array(emoji, "roles"))),
                         (char *) json_serialize_to_string(json_object_get_wrapping_value(json_object_get_object(emoji, "user"))),
                         json_object_get_boolean(emoji, "require_colons"),
                         json_object_get_boolean(emoji, "managed"),
                         json_object_get_boolean(emoji, "animated"),
                         json_object_get_boolean(emoji, "available")
    };

    return result;
}
