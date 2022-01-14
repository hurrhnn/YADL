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

#include "reaction.h"

reaction_t *parse_reaction(JSON_Value *reaction_value) {
    JSON_Object *reaction = json_object(reaction_value);
    reaction_t *result = yadl_malloc(sizeof(reaction_t));

    *result = (reaction_t) {(int) json_object_get_number(reaction, "count"),
                            yadl_json_boolean_null_check(json_object_get_boolean(reaction, "me")),
                            parse_emoji(json_object_get_wrapping_value(json_object_get_object(reaction, "emoji")))
    };

    return result;
}

JSON_Value *struct_reaction(reaction_t *reaction) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    json_object_set_number(result, "count", reaction->count);
    json_object_set_boolean(result, "me", reaction->me);
    json_object_set_value(result, "emoji", struct_emoji(reaction->emoji));

    return json_object_get_wrapping_value(result);
}
