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

#include "thread.h"

thread_metadata_t *parse_thread_metadata(JSON_Value *thread_metadata_value) {
    JSON_Object *thread_metadata = json_object(thread_metadata_value);
    thread_metadata_t *result = yadl_malloc(sizeof(thread_metadata_t), true);

    *result = (thread_metadata_t) {yadl_json_boolean_null_check(json_object_get_boolean(thread_metadata, "archived")),
                                   (int) json_object_get_number(thread_metadata, "auto_archive_duration"),
                                   (char *) json_object_get_string(thread_metadata, "archive_timestamp"),
                                   yadl_json_boolean_null_check(json_object_get_boolean(thread_metadata, "locked")),
                                   yadl_json_boolean_null_check(json_object_get_boolean(thread_metadata, "invitable"))
    };

    return result;
}

thread_member_t *parse_thread_member(JSON_Value *thread_member_value) {
    JSON_Object *thread_member = json_object(thread_member_value);
    thread_member_t *result = yadl_malloc(sizeof(thread_member_t), true);

    *result = (thread_member_t) {(char *) json_object_get_string(thread_member, "id"),
                                 (char *) json_object_get_string(thread_member, "user_id"),
                                 (char *) json_object_get_string(thread_member, "join_timestamp"),
                                 (int) json_object_get_number(thread_member, "flags")
    };

    return result;
}
