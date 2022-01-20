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

#include "json.h"

JSON_Object *yadl_json_object_builder(const char *raw) {
    return raw == NULL ? json_value_get_object(json_value_init_object()) : json_object(json_parse_string(raw));
}

JSON_Array *yadl_json_array_builder(const char *raw) {
    return raw == NULL ? json_value_get_array(json_value_init_array()) : json_array(json_parse_string(raw));
}

bool yadl_json_boolean_null_check(int result) {
    return result == -1 ? false : result;
}

void yadl_json_lws_write(struct lws *client_wsi, JSON_Object *root_object) {
    char *json_payload = yadl_malloc(YADL_LARGE_SIZE);
    json_serialize_to_buffer_pretty(json_object_get_wrapping_value(root_object), json_payload + LWS_PRE, YADL_LARGE_SIZE - LWS_PRE);

    lws_write(client_wsi, (unsigned char *) json_payload + LWS_PRE, strlen(json_payload + LWS_PRE), LWS_WRITE_TEXT);
    json_value_free(json_object_get_wrapping_value(root_object));
}
