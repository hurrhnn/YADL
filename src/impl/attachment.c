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

#include "attachment.h"

attachment_t *parse_attachment(JSON_Value *attachment_value) {
    JSON_Object *attachment = json_object(attachment_value);
    attachment_t *result = yadl_malloc(sizeof(attachment_t), true);

    *result = (attachment_t) {(char *) json_object_get_string(attachment, "filename"),
                              (char *) json_object_get_string(attachment, "description"),
                              (char *) json_object_get_string(attachment, "content_type"),
                              (int) json_object_get_number(attachment, "size"),
                              (char *) json_object_get_string(attachment, "url"),
                              (char *) json_object_get_string(attachment, "proxy_url"),
                              (int) json_object_get_number(attachment, "height"),
                              (int) json_object_get_number(attachment, "width"),
                              yadl_json_boolean_null_check(json_object_get_boolean(attachment, "ephemeral"))
    };

    return result;
}
