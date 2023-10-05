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

#include <yadl/impl/webhook.h>

webhook_t *parse_webhook(JSON_Value *webhook_value) {
    JSON_Object *webhook = json_object(webhook_value);
    webhook_t *result = yadl_malloc(sizeof(webhook_t));

    *result = (webhook_t) {(char *) json_object_get_string(webhook, "id"),
                           (int) json_object_get_number(webhook, "type"),
                           (char *) json_object_get_string(webhook, "guild_id"),
                           (char *) json_object_get_string(webhook, "channel_id"),
                           parse_user(json_object_get_wrapping_value(json_object_get_object(webhook, "user"))),
                           (char *) json_object_get_string(webhook, "name"),
                           (char *) json_object_get_string(webhook, "avatar"),
                           (char *) json_object_get_string(webhook, "token"),
                           (char *) json_object_get_string(webhook, "application_id"),
                           parse_guild(json_object_get_wrapping_value(json_object_get_object(webhook, "source_guild"))),
                           parse_channel(json_object_get_wrapping_value(json_object_get_object(webhook, "source_channel"))),
                           (char *) json_object_get_string(webhook, "url")
    };

    return result;
}

JSON_Value *struct_webhook(webhook_t *webhook) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    json_object_set_string(result, "id", webhook->id);
    json_object_set_number(result, "type", webhook->type);
    json_object_set_string(result, "guild_id", webhook->guild_id);
    json_object_set_string(result, "channel_id", webhook->channel_id);
    json_object_set_value(result, "user", struct_user(webhook->user));
    json_object_set_string(result, "name", webhook->name);
    json_object_set_string(result, "avatar", webhook->avatar);
    json_object_set_string(result, "token", webhook->token);
    json_object_set_string(result, "application_id", webhook->application_id);
    json_object_set_value(result, "source_guild", struct_guild(webhook->source_guild));
    json_object_set_value(result, "source_channel", struct_channel(webhook->source_channel));
    json_object_set_string(result, "url", webhook->url);

    return json_object_get_wrapping_value(result);
}

