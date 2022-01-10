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

guild_t *parse_guild(JSON_Value *guild_value) {
    JSON_Object *guild = json_object(guild_value);
    guild_t *result = yadl_malloc(sizeof(guild_t), true);

    *result = (guild_t) {(char *) json_object_get_string(guild, "id"),
                         (char *) json_object_get_string(guild, "name"),
                         (char *) json_object_get_string(guild, "icon"),
                         (char *) json_object_get_string(guild, "icon_hash"),
                         (char *) json_object_get_string(guild, "splash"),
                         (char *) json_object_get_string(guild, "discovery_splash"),
                         yadl_json_boolean_null_check(json_object_get_boolean(guild, "owner")),
                         (char *) json_object_get_string(guild, "owner_id"),
                         (char *) json_object_get_string(guild, "permissions"),
                         (char *) json_object_get_string(guild, "region"),
                         (char *) json_object_get_string(guild, "afk_channel_id"),
                         (int) json_object_get_number(guild, "afk_timeout"),
                         yadl_json_boolean_null_check(json_object_get_boolean(guild, "widget_enabled")),
                         (char *) json_object_get_string(guild, "widget_channel_id"),
                         (int) json_object_get_number(guild, "verification_level"),
                         (int) json_object_get_number(guild, "default_message_notifications"),
                         (int) json_object_get_number(guild, "explicit_content_filter"),
                         (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(guild, "roles"))),
                         (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(guild, "emojis"))),
                         (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(guild, "features"))),
                         (int) json_object_get_number(guild, "mfa_level"),
                         (char *) json_object_get_string(guild, "application_id"),
                         (char *) json_object_get_string(guild, "system_channel_id"),
                         (int) json_object_get_number(guild, "system_channel_flags"),
                         (char *) json_object_get_string(guild, "rules_channel_id"),
                         (char *) json_object_get_string(guild, "joined_at"),
                         yadl_json_boolean_null_check(json_object_get_boolean(guild, "large")),
                         yadl_json_boolean_null_check(json_object_get_boolean(guild, "unavailable")),
                         (int) json_object_get_number(guild, "member_count"),
                         (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(guild, "voice_states"))),
                         (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(guild, "members"))),
                         (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(guild, "channels"))),
                         (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(guild, "threads"))),
                         (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(guild, "presences"))),
                         (int) json_object_get_number(guild, "max_presences"),
                         (int) json_object_get_number(guild, "max_members"),
                         (char *) json_object_get_string(guild, "vanity_url_code"),
                         (char *) json_object_get_string(guild, "description"),
                         (char *) json_object_get_string(guild, "banner"),
                         (int) json_object_get_number(guild, "premium_tier"),
                         (int) json_object_get_number(guild, "premium_subscription_count"),
                         (char *) json_object_get_string(guild, "preferred_locale"),
                         (char *) json_object_get_string(guild, "public_updates_channel_id"),
                         (int) json_object_get_number(guild, "max_video_channel_users"),
                         (int) json_object_get_number(guild, "approximate_member_count"),
                         (int) json_object_get_number(guild, "approximate_presence_count"),
                         (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(guild, "welcome_screen"))),
                         (int) json_object_get_number(guild, "nsfw_level"),
                         (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(guild, "stage_instances"))),
                         (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(guild, "stickers"))),
                         (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(guild, "guild_scheduled_events"))),
                         yadl_json_boolean_null_check(json_object_get_boolean(guild, "premium_progress_bar_enabled"))
    };

    return result;
}

guild_preview_t *parse_guild_preview(JSON_Value *guild_preview_value) {
    JSON_Object *guild_preview = json_object(guild_preview_value);
    guild_preview_t *result = yadl_malloc(sizeof(guild_preview_t), true);

    *result = (guild_preview_t) {(char *) json_object_get_string(guild_preview, "id"),
                                 (char *) json_object_get_string(guild_preview, "name"),
                                 (char *) json_object_get_string(guild_preview, "icon"),
                                 (char *) json_object_get_string(guild_preview, "splash"),
                                 (char *) json_object_get_string(guild_preview, "discovery_splash"),
                                 (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(guild_preview, "emojis"))),
                                 (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(guild_preview, "features"))),
                                 (int) json_object_get_number(guild_preview, "approximate_member_count"),
                                 (int) json_object_get_number(guild_preview, "approximate_presence_count"),
                                 (char *) json_object_get_string(guild_preview, "description")
    };

    return result;
}

guild_widget_t *parse_guild_widget(JSON_Value *guild_widget_value) {
    JSON_Object *guild_widget = json_object(guild_widget_value);
    guild_widget_t *result = yadl_malloc(sizeof(guild_widget_t), true);

    *result = (guild_widget_t) {yadl_json_boolean_null_check(json_object_get_boolean(guild_widget, "enabled")),
                                (char *) json_object_get_string(guild_widget, "channel_id")
    };

    return result;
}

guild_member_t *parse_guild_member(JSON_Value *guild_member_value) {
    JSON_Object *guild_member = json_object(guild_member_value);
    guild_member_t *result = yadl_malloc(sizeof(guild_member_t), true);

    *result = (guild_member_t) {(char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(guild_member, "user"))),
                                (char *) json_object_get_string(guild_member, "nick"),
                                (char *) json_object_get_string(guild_member, "avatar"),
                                (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(guild_member, "roles"))),
                                (char *) json_object_get_string(guild_member, "joined_at"),
                                (char *) json_object_get_string(guild_member, "premium_since"),
                                yadl_json_boolean_null_check(json_object_get_boolean(guild_member, "deaf")),
                                yadl_json_boolean_null_check(json_object_get_boolean(guild_member, "mute")),
                                yadl_json_boolean_null_check(json_object_get_boolean(guild_member, "pending")),
                                (char *) json_object_get_string(guild_member, "permissions"),
                                (char *) json_object_get_string(guild_member, "communication_disabled_until")
    };

    return result;
}

ban_t *parse_ban(JSON_Value *ban_value) {
    JSON_Object *ban = json_object(ban_value);
    ban_t *result = yadl_malloc(sizeof(ban_t), true);

    *result = (ban_t) {(char *) json_object_get_string(ban, "reason"),
                       (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(ban, "user")))
    };

    return result;
}



welcome_screen_t *parse_welcome_screen(JSON_Value *welcome_screen_value) {
    JSON_Object *welcome_screen = json_object(welcome_screen_value);
    welcome_screen_t *result = yadl_malloc(sizeof(welcome_screen_t), true);

    *result = (welcome_screen_t) {(char *) json_object_get_string(welcome_screen, "description"),
                                  (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(welcome_screen, "welcome_channels")))
    };

    return result;
}



welcome_screen_channel_t *parse_welcome_screen_channel(JSON_Value *welcome_screen_channel_value) {
    JSON_Object *welcome_screen_channel = json_object(welcome_screen_channel_value);
    welcome_screen_channel_t *result = yadl_malloc(sizeof(welcome_screen_channel_t), true);

    *result = (welcome_screen_channel_t) {(char *) json_object_get_string(welcome_screen_channel, "channel_id"),
                                          (char *) json_object_get_string(welcome_screen_channel, "description"),
                                          (char *) json_object_get_string(welcome_screen_channel, "emoji_id"),
                                          (char *) json_object_get_string(welcome_screen_channel, "emoji_name")
    };

    return result;
}



guild_scheduled_event_t *parse_guild_scheduled_event(JSON_Value *guild_scheduled_event_value) {
    JSON_Object *guild_scheduled_event = json_object(guild_scheduled_event_value);
    guild_scheduled_event_t *result = yadl_malloc(sizeof(guild_scheduled_event_t), true);

    *result = (guild_scheduled_event_t) {(char *) json_object_get_string(guild_scheduled_event, "id"),
                                         (char *) json_object_get_string(guild_scheduled_event, "guild_id"),
                                         (char *) json_object_get_string(guild_scheduled_event, "channel_id"),
                                         (char *) json_object_get_string(guild_scheduled_event, "creator_id"),
                                         (char *) json_object_get_string(guild_scheduled_event, "name"),
                                         (char *) json_object_get_string(guild_scheduled_event, "description"),
                                         (char *) json_object_get_string(guild_scheduled_event, "scheduled_start_time"),
                                         (char *) json_object_get_string(guild_scheduled_event, "scheduled_end_time"),
                                         (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(guild_scheduled_event, "privacy_level"))),
                                         (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(guild_scheduled_event, "status"))),
                                         (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(guild_scheduled_event, "entity_type"))),
                                         (char *) json_object_get_string(guild_scheduled_event, "entity_id"),
                                         (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(guild_scheduled_event, "entity_metadata"))),
                                         (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(guild_scheduled_event, "creator"))),
                                         (int) json_object_get_number(guild_scheduled_event, "user_count")
    };

    return result;
}



guild_scheduled_event_user_t *parse_guild_scheduled_event_user(JSON_Value *guild_scheduled_event_user_value) {
    JSON_Object *guild_scheduled_event_user = json_object(guild_scheduled_event_user_value);
    guild_scheduled_event_user_t *result = yadl_malloc(sizeof(guild_scheduled_event_user_t), true);

    *result = (guild_scheduled_event_user_t) {(char *) json_object_get_string(guild_scheduled_event_user, "guild_scheduled_event_id"),
                                              (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(guild_scheduled_event_user, "user"))),
                                              (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(guild_scheduled_event_user, "member")))
    };

    return result;
}



guild_template_t *parse_guild_template(JSON_Value *guild_template_value) {
    JSON_Object *guild_template = json_object(guild_template_value);
    guild_template_t *result = yadl_malloc(sizeof(guild_template_t), true);

    *result = (guild_template_t) {(char *) json_object_get_string(guild_template, "code"),
                                  (char *) json_object_get_string(guild_template, "name"),
                                  (char *) json_object_get_string(guild_template, "description"),
                                  (int) json_object_get_number(guild_template, "usage_count"),
                                  (char *) json_object_get_string(guild_template, "creator_id"),
                                  (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(guild_template, "creator"))),
                                  (char *) json_object_get_string(guild_template, "created_at"),
                                  (char *) json_object_get_string(guild_template, "updated_at"),
                                  (char *) json_object_get_string(guild_template, "source_guild_id"),
                                  (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(guild_template, "serialized_source_guild"))),
                                  yadl_json_boolean_null_check(json_object_get_boolean(guild_template, "is_dirty"))
    };

    return result;
}
