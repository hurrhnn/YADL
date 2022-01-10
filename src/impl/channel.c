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

#include "channel.h"

channel_t *parse_channel(JSON_Value *channel_value) {
    JSON_Object *channel = json_object(channel_value);
    channel_t *result = yadl_malloc(sizeof(channel_t), true);
    *result = (channel_t) {(char *) json_object_get_string(channel, "id"),
                           (int) json_object_get_number(channel, "type"),
                           (char *) json_object_get_string(channel, "guild_id"),
                           (int) json_object_get_number(channel, "position"),
                           (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(channel, "permission_overwrites"))),
                           (char *) json_object_get_string(channel, "name"),
                           (char *) json_object_get_string(channel, "topic"),
                           yadl_json_boolean_null_check(json_object_get_boolean(channel, "nsfw")),
                           (char *) json_object_get_string(channel, "last_message_id"),
                           (int) json_object_get_number(channel, "bitrate"),
                           (int) json_object_get_number(channel, "user_limit"),
                           (int) json_object_get_number(channel, "rate_limit_per_user"),
                           (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(channel, "recipients"))),
                           (char *) json_object_get_string(channel, "icon"),
                           (char *) json_object_get_string(channel, "owner_id"),
                           (char *) json_object_get_string(channel, "application_id"),
                           (char *) json_object_get_string(channel, "parent_id"),
                           (char *) json_object_get_string(channel, "last_pin_timestamp"),
                           (char *) json_object_get_string(channel, "rtc_region"),
                           (int) json_object_get_number(channel, "video_quality_mode"),
                           (int) json_object_get_number(channel, "message_count"),
                           (int) json_object_get_number(channel, "member_count"),
                           (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(channel, "thread_metadata"))),
                           (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(channel, "member"))),
                           (int) json_object_get_number(channel, "default_auto_archive_duration"),
                           (char *) json_object_get_string(channel, "permissions")
    };

    return result;
}

channel_mention_t *parse_channel_mention(JSON_Value *channel_mention_value) {
    JSON_Object *channel_mention = json_object(channel_mention_value);
    channel_mention_t *result = yadl_malloc(sizeof(channel_mention_t), true);
    *result = (channel_mention_t) {(char *) json_object_get_string(channel_mention, "id"),
                                   (char *) json_object_get_string(channel_mention, "guild_id"),
                                   (int) json_object_get_number(channel_mention, "type"),
                                   (char *) json_object_get_string(channel_mention, "name")
    };

    return result;
}

allowed_mentions_t *parse_allowed_mentions(JSON_Value *allowed_mentions_value) {
    JSON_Object *allowed_mentions = json_object(allowed_mentions_value);
    allowed_mentions_t *result = yadl_malloc(sizeof(allowed_mentions_t), true);

    *result = (allowed_mentions_t) {(char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(allowed_mentions, "parse"))),
                                    (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(allowed_mentions, "roles"))),
                                    (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(allowed_mentions, "users"))),
                                    yadl_json_boolean_null_check(json_object_get_boolean(allowed_mentions, "replied_user"))
    };

    return result;
}
