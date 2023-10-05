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

#include <yadl/impl/thread.h>

thread_metadata_t *parse_thread_metadata(JSON_Value *thread_metadata_value) {
    JSON_Object *thread_metadata = json_object(thread_metadata_value);
    thread_metadata_t *result = yadl_malloc(sizeof(thread_metadata_t));

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
    thread_member_t *result = yadl_malloc(sizeof(thread_member_t));

    *result = (thread_member_t) {(char *) json_object_get_string(thread_member, "id"),
                                 (char *) json_object_get_string(thread_member, "user_id"),
                                 (char *) json_object_get_string(thread_member, "join_timestamp"),
                                 (int) json_object_get_number(thread_member, "flags")
    };

    return result;
}

JSON_Value *struct_thread_member(thread_member_t *thread_member) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    json_object_set_string(result, "id", thread_member->id);
    json_object_set_string(result, "user_id", thread_member->user_id);
    json_object_set_string(result, "join_timestamp", thread_member->join_timestamp);
    json_object_set_number(result, "flags", thread_member->flags);

    return json_object_get_wrapping_value(result);
}
JSON_Value *struct_thread_metadata(thread_metadata_t *thread_metadata) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    json_object_set_boolean(result, "archived", thread_metadata->archived);
    json_object_set_number(result, "auto_archive_duration", thread_metadata->auto_archive_duration);
    json_object_set_string(result, "archive_timestamp", thread_metadata->archive_timestamp);
    json_object_set_boolean(result, "locked", thread_metadata->locked);
    json_object_set_boolean(result, "invitable", thread_metadata->invitable);

    return json_object_get_wrapping_value(result);
}
