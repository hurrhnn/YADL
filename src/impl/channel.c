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
#include "impl.h"

channel_t *parse_channel(JSON_Value *channel_value) {
    JSON_Object *channel = json_object(channel_value);
    channel_t *result = yadl_malloc(sizeof(channel_t));
    *result = (channel_t) {(char *) json_object_get_string(channel, "id"),
                           (int) json_object_get_number(channel, "type"),
                           (char *) json_object_get_string(channel, "guild_id"),
                           (int) json_object_get_number(channel, "position"),
                           yadl_object_array_parse(YADL_OBJECT_OVERWRITE, (json_object_get_array(channel, "permission_overwrites"))),
                           (char *) json_object_get_string(channel, "name"),
                           (char *) json_object_get_string(channel, "topic"),
                           yadl_json_boolean_null_check(json_object_get_boolean(channel, "nsfw")),
                           (char *) json_object_get_string(channel, "last_message_id"),
                           (int) json_object_get_number(channel, "bitrate"),
                           (int) json_object_get_number(channel, "user_limit"),
                           (int) json_object_get_number(channel, "rate_limit_per_user"),
                           yadl_object_array_parse(YADL_OBJECT_USER, (json_object_get_array(channel, "recipients"))),
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
                           parse_guild_member(json_object_get_wrapping_value(json_object_get_object(channel, "member"))),
                           (int) json_object_get_number(channel, "default_auto_archive_duration"),
                           (char *) json_object_get_string(channel, "permissions")
    };

    return result;
}

channel_mention_t *parse_channel_mention(JSON_Value *channel_mention_value) {
    JSON_Object *channel_mention = json_object(channel_mention_value);
    channel_mention_t *result = yadl_malloc(sizeof(channel_mention_t));
    *result = (channel_mention_t) {(char *) json_object_get_string(channel_mention, "id"),
                                   (char *) json_object_get_string(channel_mention, "guild_id"),
                                   (int) json_object_get_number(channel_mention, "type"),
                                   (char *) json_object_get_string(channel_mention, "name")
    };

    return result;
}

allowed_mentions_t *parse_allowed_mentions(JSON_Value *allowed_mentions_value) {
    JSON_Object *allowed_mentions = json_object(allowed_mentions_value);
    allowed_mentions_t *result = yadl_malloc(sizeof(allowed_mentions_t));

    *result = (allowed_mentions_t) {(char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(allowed_mentions, "parse"))),
                                    (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(allowed_mentions, "roles"))),
                                    (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(allowed_mentions, "users"))),
                                    yadl_json_boolean_null_check(json_object_get_boolean(allowed_mentions, "replied_user"))
    };

    return result;
}

overwrite_t *parse_overwrite(JSON_Value *overwrite_value) {
    JSON_Object *overwrite = json_object(overwrite_value);
    overwrite_t *result = yadl_malloc(sizeof(overwrite_t));

    *result = (overwrite_t) {(char *) json_object_get_string(overwrite, "id"),
                             (int) json_object_get_number(overwrite, "type"),
                             (char *) json_object_get_string(overwrite, "allow"),
                             (char *) json_object_get_string(overwrite, "deny")
    };

    return result;
}

JSON_Value *struct_overwrite(overwrite_t *overwrite) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    if(overwrite != NULL) {
        json_object_set_string(result, "id", overwrite->id);
        json_object_set_number(result, "type", overwrite->type);
        json_object_set_string(result, "allow", overwrite->allow);
        json_object_set_string(result, "deny", overwrite->deny);
    }

    return json_object_get_wrapping_value(result);
}
JSON_Value *struct_allowed_mentions(allowed_mentions_t *allowed_mentions) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    if(allowed_mentions != NULL) {
        json_object_set_string(result, "parse", allowed_mentions->parse);
        json_object_set_string(result, "roles", allowed_mentions->roles);
        json_object_set_string(result, "users", allowed_mentions->users);
        json_object_set_boolean(result, "replied_user", allowed_mentions->replied_user);
    }

    return json_object_get_wrapping_value(result);
}
JSON_Value *struct_channel_mention(channel_mention_t *channel_mention) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    if(channel_mention != NULL) {
        json_object_set_string(result, "id", channel_mention->id);
        json_object_set_string(result, "guild_id", channel_mention->guild_id);
        json_object_set_number(result, "type", channel_mention->type);
        json_object_set_string(result, "name", channel_mention->name);
    }

    return json_object_get_wrapping_value(result);
}
JSON_Value *struct_channel(channel_t *channel) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    if(channel != NULL) {
        json_object_set_string(result, "id", channel->id);
        json_object_set_number(result, "type", channel->type);
        json_object_set_string(result, "guild_id", channel->guild_id);
        json_object_set_number(result, "position", channel->position);

        JSON_Array *permission_overwrites = yadl_json_array_builder(NULL);
        if(channel->permission_overwrites != NULL) {
            for (int i=0; i<channel->permission_overwrites->size; i++)
                json_array_append_value(permission_overwrites, struct_overwrite((overwrite_t *)channel->permission_overwrites->array[i]));
        }
        json_object_set_value(result, "permission_overwrites", json_array_get_wrapping_value(permission_overwrites));

        json_object_set_string(result, "name", channel->name);
        json_object_set_string(result, "topic", channel->topic);
        json_object_set_boolean(result, "nsfw", channel->nsfw);
        json_object_set_string(result, "last_message_id", channel->last_message_id);
        json_object_set_number(result, "bitrate", channel->bitrate);
        json_object_set_number(result, "user_limit", channel->user_limit);
        json_object_set_number(result, "rate_limit_per_user", channel->rate_limit_per_user);

        JSON_Array *recipients = yadl_json_array_builder(NULL);
        if(channel->recipients != NULL) {
            for (int i=0; i<channel->recipients->size; i++)
                json_array_append_value(recipients, struct_user((user_t *)channel->recipients->array[i]));
        }
        json_object_set_value(result, "recipients", json_array_get_wrapping_value(recipients));

        json_object_set_string(result, "icon", channel->icon);
        json_object_set_string(result, "owner_id", channel->owner_id);
        json_object_set_string(result, "application_id", channel->application_id);
        json_object_set_string(result, "parent_id", channel->parent_id);
        json_object_set_string(result, "last_pin_timestamp", channel->last_pin_timestamp);
        json_object_set_string(result, "rtc_region", channel->rtc_region);
        json_object_set_number(result, "video_quality_mode", channel->video_quality_mode);
        json_object_set_number(result, "message_count", channel->message_count);
        json_object_set_number(result, "member_count", channel->member_count);
        json_object_set_string(result, "thread_metadata", channel->thread_metadata);
        json_object_set_value(result, "member", struct_guild_member(channel->member));
        json_object_set_number(result, "default_auto_archive_duration", channel->default_auto_archive_duration);
        json_object_set_string(result, "permissions", channel->permissions);
    }

    return json_object_get_wrapping_value(result);
}
