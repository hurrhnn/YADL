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

#include "message.h"

message_t *parse_message(JSON_Value *message_value) {
    JSON_Object *message = json_object(message_value);
    message_t *result = yadl_malloc(sizeof(message_t), true);

    *result = (message_t) {(char *) json_object_get_string(message, "channel_id"),
                           (char *) json_object_get_string(message, "guild_id"),
                           (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(message, "author"))),
                           (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(message, "member"))),
                           (char *) json_object_get_string(message, "content"),
                           (char *) json_object_get_string(message, "timestamp"),
                           (char *) json_object_get_string(message, "edited_timestamp"),
                           yadl_json_boolean_null_check(json_object_get_boolean(message, "tts")),
                           yadl_json_boolean_null_check(json_object_get_boolean(message, "mention_everyone")),
                           (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(message, "mentions"))),
                           (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(message, "mention_roles"))),
                           (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(message, "mention_channels"))),
                           (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(message, "attachments"))),
                           (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(message, "embeds"))),
                           (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(message, "reactions"))),
                           (char *) json_object_get_string(message, "nonce"),
                           yadl_json_boolean_null_check(json_object_get_boolean(message, "pinned")),
                           (char *) json_object_get_string(message, "webhook_id"),
                           (int) json_object_get_number(message, "type"),
                           (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(message, "activity"))),
                           (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(message, "application"))),
                           (char *) json_object_get_string(message, "application_id"),
                           (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(message, "message_reference"))),
                           (int) json_object_get_number(message, "flags"),
                           (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(message, "referenced_message"))),
                           (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(message, "interaction"))),
                           (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(message, "thread"))),
                           (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(message, "components"))),
                           (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(message, "sticker_items"))),
                           (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(message, "stickers")))
    };

    return result;
}

message_activity_t *parse_message_activity(JSON_Value *message_activity_value) {
    JSON_Object *message_activity = json_object(message_activity_value);
    message_activity_t *result = yadl_malloc(sizeof(message_activity_t), true);
    *result = (message_activity_t) {(int) json_object_get_number(message_activity, "type"),
                                    (char *) json_object_get_string(message_activity, "party_id")
    };

    return result;
}



message_reference_t *parse_message_reference(JSON_Value *message_reference_value) {
    JSON_Object *message_reference = json_object(message_reference_value);
    message_reference_t *result = yadl_malloc(sizeof(message_reference_t), true);
    *result = (message_reference_t) {(char *) json_object_get_string(message_reference, "message_id"),
                                     (char *) json_object_get_string(message_reference, "channel_id"),
                                     (char *) json_object_get_string(message_reference, "guild_id"),
                                     yadl_json_boolean_null_check(json_object_get_boolean(message_reference, "fail_if_not_exists"))
    };

    return result;
}

followed_channel_t *parse_followed_channel(JSON_Value *followed_channel_value) {
    JSON_Object *followed_channel = json_object(followed_channel_value);
    followed_channel_t *result = yadl_malloc(sizeof(followed_channel_t), true);
    *result = (followed_channel_t) {(char *) json_object_get_string(followed_channel, "channel_id"),
                                    (char *) json_object_get_string(followed_channel, "webhook_id")
    };

    return result;
}