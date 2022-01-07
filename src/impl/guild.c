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

#include "guild.h"
#include "../utils/utils.h"

guild_t *parse_guild(JSON_Value *guild_value) {
    JSON_Object *guild = json_object(guild_value);
    guild_t *result = yadl_malloc(sizeof(guild_t), true);
    *result = (guild_t) { (char *) json_object_get_string(guild, "id"),
                          (char *) json_object_get_string(guild, "name"),
                          (char *) json_object_get_string(guild, "icon"),
                          (char *) json_object_get_string(guild, "splash"),
                          (char *) json_object_get_string(guild, "discovery_splash"),
                          json_object_get_boolean(guild, "owner"),
                          (char *) json_object_get_string(guild, "owner_id"),
                          (char *) json_object_get_string(guild, "permissions"),
                          (char *) json_object_get_string(guild, "afk_channel_id"),
                          (int32_t) json_object_get_number(guild, "afk_timeout"),
                           json_object_get_boolean(guild, "widget_enabled"),
                          (char *) json_object_get_string(guild, "widget_channel_id"),
                          (int8_t) json_object_get_number(guild, "verification_level"),
                          (int8_t) json_object_get_number(guild, "default_message_notifications"),
                          (int8_t) json_object_get_number(guild, "explicit_content_filter"),
                          (char *) json_serialize_to_string(json_array_get_wrapping_value(json_object_get_array(guild, "roles"))),
                          (char *) json_serialize_to_string(json_array_get_wrapping_value(json_object_get_array(guild, "emojis"))),
                          (char *) json_serialize_to_string(json_array_get_wrapping_value(json_object_get_array(guild, "features"))),
                          (int8_t) json_object_get_number(guild, "mfa_level"),
                          (char *) json_object_get_string(guild, "application_id"),
                          (char *) json_object_get_string(guild, "system_channel_id"),
                          (int8_t) json_object_get_number(guild, "system_channel_flags"),
                          (char *) json_object_get_string(guild, "rules_channel_id"),
                          (char *) json_object_get_string(guild, "joined_at"),
                          json_object_get_boolean(guild, "large"),
                          json_object_get_boolean(guild, "unavailable"),
                          (int32_t)json_object_get_number(guild, "member_count"),
                          (char *) json_serialize_to_string(json_array_get_wrapping_value(json_object_get_array(guild, "voice_states"))),
                          (char *) json_serialize_to_string(json_array_get_wrapping_value(json_object_get_array(guild, "members"))),
                          (char *) json_serialize_to_string(json_array_get_wrapping_value(json_object_get_array(guild, "channels"))),
                          (char *) json_serialize_to_string(json_array_get_wrapping_value(json_object_get_array(guild, "threads"))),
                          (char *) json_serialize_to_string(json_array_get_wrapping_value(json_object_get_array(guild, "presences"))),
                          (int32_t) json_object_get_number(guild, "max_members"),
                          (char *) json_object_get_string(guild, "vanity_url_code"),
                          (char *) json_object_get_string(guild, "description"),
                          (char *) json_object_get_string(guild, "banner"),
                          (int8_t) json_object_get_number(guild, "premium_tier"),
                          (int32_t) json_object_get_number(guild, "premium_subscription_count"),
                          (char *) json_object_get_string(guild, "preferred_locale"),
                          (char *) json_object_get_string(guild, "public_updates_channel_id"),
                          (int32_t) json_object_get_number(guild, "max_video_channel_users"),
                          (int32_t) json_object_get_number(guild, "approximate_member_count"),
                          (int32_t) json_object_get_number(guild, "approximate_presence_count"),
                          (char *) json_serialize_to_string(json_array_get_wrapping_value(json_object_get_array(guild, "welcome_screen"))),
                          (int8_t) json_object_get_number(guild, "nsfw_level"),
                          json_serialize_to_string(json_array_get_wrapping_value(json_object_get_array(guild, "stage_instances"))),
                          json_serialize_to_string(json_array_get_wrapping_value(json_object_get_array(guild, "stickers"))),
                          json_serialize_to_string(json_array_get_wrapping_value(json_object_get_array(guild, "guild_scheduled_events"))),
                          json_object_get_array(guild, "premium_progress_bar_enabled")
                          };
    return result;
}
