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

#include "webhook.h"

webhook_t *parse_webhook(JSON_Value *webhook_value) {
    JSON_Object *webhook = json_object(webhook_value);
    webhook_t *result = yadl_malloc(sizeof(webhook_t));

    *result = (webhook_t) {(char *) json_object_get_string(webhook, "id"),
                           (int) json_object_get_number(webhook, "type"),
                           (char *) json_object_get_string(webhook, "guild_id"),
                           (char *) json_object_get_string(webhook, "channel_id"),
                           (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(webhook, "user"))),
                           (char *) json_object_get_string(webhook, "name"),
                           (char *) json_object_get_string(webhook, "avatar"),
                           (char *) json_object_get_string(webhook, "token"),
                           (char *) json_object_get_string(webhook, "application_id"),
                           (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(webhook, "source_guild"))),
                           (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(webhook, "source_channel"))),
                           (char *) json_object_get_string(webhook, "url")
    };

    return result;
}
