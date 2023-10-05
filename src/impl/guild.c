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

#include <yadl/impl/guild.h>
#include <yadl/impl/impl.h>

guild_t *parse_guild(JSON_Value *guild_value) {
    JSON_Object *guild = json_object(guild_value);
    guild_t *result = yadl_malloc(sizeof(guild_t));

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
                         yadl_object_array_parse(YADL_OBJECT_EMOJI,(json_object_get_array(guild, "emojis"))),
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
                         yadl_object_array_parse(YADL_OBJECT_VOICE_STATE,(json_object_get_array(guild, "voice_states"))),
                         yadl_object_array_parse(YADL_OBJECT_GUILD_MEMBER,(json_object_get_array(guild, "members"))),
                         yadl_object_array_parse(YADL_OBJECT_CHANNEL,(json_object_get_array(guild, "channels"))),
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
                         parse_welcome_screen(json_object_get_wrapping_value(json_object_get_object(guild, "welcome_screen"))),
                         (int) json_object_get_number(guild, "nsfw_level"),
                         (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(guild, "stage_instances"))),
                         yadl_object_array_parse(YADL_OBJECT_STICKER,(json_object_get_array(guild, "stickers"))),
                         yadl_object_array_parse(YADL_OBJECT_GUILD_SCHEDULED_EVENT,(json_object_get_array(guild, "guild_scheduled_events"))),
                         yadl_json_boolean_null_check(json_object_get_boolean(guild, "premium_progress_bar_enabled"))
    };

    return result;
}

guild_preview_t *parse_guild_preview(JSON_Value *guild_preview_value) {
    JSON_Object *guild_preview = json_object(guild_preview_value);
    guild_preview_t *result = yadl_malloc(sizeof(guild_preview_t));

    *result = (guild_preview_t) {(char *) json_object_get_string(guild_preview, "id"),
                                 (char *) json_object_get_string(guild_preview, "name"),
                                 (char *) json_object_get_string(guild_preview, "icon"),
                                 (char *) json_object_get_string(guild_preview, "splash"),
                                 (char *) json_object_get_string(guild_preview, "discovery_splash"),
                                 yadl_object_array_parse(YADL_OBJECT_EMOJI, json_object_get_array(guild_preview, "emojis")),
                                 (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(guild_preview, "features"))),
                                 (int) json_object_get_number(guild_preview, "approximate_member_count"),
                                 (int) json_object_get_number(guild_preview, "approximate_presence_count"),
                                 (char *) json_object_get_string(guild_preview, "description")
    };

    return result;
}

guild_widget_t *parse_guild_widget(JSON_Value *guild_widget_value) {
    JSON_Object *guild_widget = json_object(guild_widget_value);
    guild_widget_t *result = yadl_malloc(sizeof(guild_widget_t));

    *result = (guild_widget_t) {yadl_json_boolean_null_check(json_object_get_boolean(guild_widget, "enabled")),
                                (char *) json_object_get_string(guild_widget, "channel_id")
    };

    return result;
}

guild_member_t *parse_guild_member(JSON_Value *guild_member_value) {
    JSON_Object *guild_member = json_object(guild_member_value);
    guild_member_t *result = yadl_malloc(sizeof(guild_member_t));

    *result = (guild_member_t) {parse_user(json_object_get_wrapping_value(json_object_get_object(guild_member, "user"))),
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
    ban_t *result = yadl_malloc(sizeof(ban_t));

    *result = (ban_t) {(char *) json_object_get_string(ban, "reason"),
                       parse_user(json_object_get_wrapping_value(json_object_get_object(ban, "user")))
    };

    return result;
}



welcome_screen_t *parse_welcome_screen(JSON_Value *welcome_screen_value) {
    JSON_Object *welcome_screen = json_object(welcome_screen_value);
    welcome_screen_t *result = yadl_malloc(sizeof(welcome_screen_t));

    *result = (welcome_screen_t) {(char *) json_object_get_string(welcome_screen, "description"),
                                  yadl_object_array_parse(YADL_OBJECT_WELCOME_SCREEN_CHANNEL, json_object_get_array(welcome_screen, "welcome_channels"))
    };

    return result;
}



welcome_screen_channel_t *parse_welcome_screen_channel(JSON_Value *welcome_screen_channel_value) {
    JSON_Object *welcome_screen_channel = json_object(welcome_screen_channel_value);
    welcome_screen_channel_t *result = yadl_malloc(sizeof(welcome_screen_channel_t));

    *result = (welcome_screen_channel_t) {(char *) json_object_get_string(welcome_screen_channel, "channel_id"),
                                          (char *) json_object_get_string(welcome_screen_channel, "description"),
                                          (char *) json_object_get_string(welcome_screen_channel, "emoji_id"),
                                          (char *) json_object_get_string(welcome_screen_channel, "emoji_name")
    };

    return result;
}



guild_scheduled_event_t *parse_guild_scheduled_event(JSON_Value *guild_scheduled_event_value) {
    JSON_Object *guild_scheduled_event = json_object(guild_scheduled_event_value);
    guild_scheduled_event_t *result = yadl_malloc(sizeof(guild_scheduled_event_t));

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
                                         parse_user(json_object_get_wrapping_value(json_object_get_object(guild_scheduled_event, "creator"))),
                                         (int) json_object_get_number(guild_scheduled_event, "user_count")
    };

    return result;
}



guild_scheduled_event_user_t *parse_guild_scheduled_event_user(JSON_Value *guild_scheduled_event_user_value) {
    JSON_Object *guild_scheduled_event_user = json_object(guild_scheduled_event_user_value);
    guild_scheduled_event_user_t *result = yadl_malloc(sizeof(guild_scheduled_event_user_t));

    *result = (guild_scheduled_event_user_t) {(char *) json_object_get_string(guild_scheduled_event_user, "guild_scheduled_event_id"),
                                              parse_user(json_object_get_wrapping_value(json_object_get_object(guild_scheduled_event_user, "user"))),
                                              parse_guild_member(json_object_get_wrapping_value(json_object_get_object(guild_scheduled_event_user, "member")))
    };

    return result;
}



guild_template_t *parse_guild_template(JSON_Value *guild_template_value) {
    JSON_Object *guild_template = json_object(guild_template_value);
    guild_template_t *result = yadl_malloc(sizeof(guild_template_t));

    *result = (guild_template_t) {(char *) json_object_get_string(guild_template, "code"),
                                  (char *) json_object_get_string(guild_template, "name"),
                                  (char *) json_object_get_string(guild_template, "description"),
                                  (int) json_object_get_number(guild_template, "usage_count"),
                                  (char *) json_object_get_string(guild_template, "creator_id"),
                                  parse_user(json_object_get_wrapping_value(json_object_get_object(guild_template, "creator"))),
                                  (char *) json_object_get_string(guild_template, "created_at"),
                                  (char *) json_object_get_string(guild_template, "updated_at"),
                                  (char *) json_object_get_string(guild_template, "source_guild_id"),
                                  parse_guild(json_object_get_wrapping_value(json_object_get_object(guild_template, "serialized_source_guild"))),
                                  yadl_json_boolean_null_check(json_object_get_boolean(guild_template, "is_dirty"))
    };

    return result;
}

JSON_Value *struct_guild_template(guild_template_t *guild_template) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    json_object_set_string(result, "code", guild_template->code);
    json_object_set_string(result, "name", guild_template->name);
    json_object_set_string(result, "description", guild_template->description);
    json_object_set_number(result, "usage_count", guild_template->usage_count);
    json_object_set_string(result, "creator_id", guild_template->creator_id);
    json_object_set_value(result, "creator", struct_user(guild_template->creator));
    json_object_set_string(result, "created_at", guild_template->created_at);
    json_object_set_string(result, "updated_at", guild_template->updated_at);
    json_object_set_string(result, "source_guild_id", guild_template->source_guild_id);
    json_object_set_value(result, "serialized_source_guild", struct_guild(guild_template->serialized_source_guild));
    json_object_set_boolean(result, "is_dirty", guild_template->is_dirty);

    return json_object_get_wrapping_value(result);
}
JSON_Value *struct_guild_scheduled_event_user(guild_scheduled_event_user_t *guild_scheduled_event_user) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    json_object_set_string(result, "guild_scheduled_event_id", guild_scheduled_event_user->guild_scheduled_event_id);
    json_object_set_value(result, "user", struct_user(guild_scheduled_event_user->user));
    json_object_set_value(result, "member", struct_guild_member(guild_scheduled_event_user->member));

    return json_object_get_wrapping_value(result);
}
JSON_Value *struct_guild_scheduled_event(guild_scheduled_event_t *guild_scheduled_event) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    json_object_set_string(result, "id", guild_scheduled_event->id);
    json_object_set_string(result, "guild_id", guild_scheduled_event->guild_id);
    json_object_set_string(result, "channel_id", guild_scheduled_event->channel_id);
    json_object_set_string(result, "creator_id", guild_scheduled_event->creator_id);
    json_object_set_string(result, "name", guild_scheduled_event->name);
    json_object_set_string(result, "description", guild_scheduled_event->description);
    json_object_set_string(result, "scheduled_start_time", guild_scheduled_event->scheduled_start_time);
    json_object_set_string(result, "scheduled_end_time", guild_scheduled_event->scheduled_end_time);
    json_object_set_string(result, "privacy_level", guild_scheduled_event->privacy_level);
    json_object_set_string(result, "status", guild_scheduled_event->status);
    json_object_set_string(result, "entity_type", guild_scheduled_event->entity_type);
    json_object_set_string(result, "entity_id", guild_scheduled_event->entity_id);
    json_object_set_string(result, "entity_metadata", guild_scheduled_event->entity_metadata);
    json_object_set_value(result, "creator", struct_user(guild_scheduled_event->creator));
    json_object_set_number(result, "user_count", guild_scheduled_event->user_count);

    return json_object_get_wrapping_value(result);
}
JSON_Value *struct_welcome_screen_channel(welcome_screen_channel_t *welcome_screen_channel) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    json_object_set_string(result, "channel_id", welcome_screen_channel->channel_id);
    json_object_set_string(result, "description", welcome_screen_channel->description);
    json_object_set_string(result, "emoji_id", welcome_screen_channel->emoji_id);
    json_object_set_string(result, "emoji_name", welcome_screen_channel->emoji_name);

    return json_object_get_wrapping_value(result);
}
JSON_Value *struct_welcome_screen(welcome_screen_t *welcome_screen) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    json_object_set_string(result, "description", welcome_screen->description);

    JSON_Array *welcome_channels = yadl_json_array_builder(NULL);
    for (int i=0; i<welcome_screen->welcome_channels->size; i++)
        json_array_append_value(welcome_channels, struct_welcome_screen_channel((welcome_screen_channel_t *)welcome_screen->welcome_channels->array[i]));


    return json_object_get_wrapping_value(result);
}
JSON_Value *struct_ban(ban_t *ban) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    json_object_set_string(result, "reason", ban->reason);
    json_object_set_value(result, "user", struct_user(ban->user));

    return json_object_get_wrapping_value(result);
}
JSON_Value *struct_guild_member(guild_member_t *guild_member) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    json_object_set_value(result, "user", struct_user(guild_member->user));
    json_object_set_string(result, "nick", guild_member->nick);
    json_object_set_string(result, "avatar", guild_member->avatar);
    json_object_set_string(result, "roles", guild_member->roles);
    json_object_set_string(result, "joined_at", guild_member->joined_at);
    json_object_set_string(result, "premium_since", guild_member->premium_since);
    json_object_set_boolean(result, "deaf", guild_member->deaf);
    json_object_set_boolean(result, "mute", guild_member->mute);
    json_object_set_boolean(result, "pending", guild_member->pending);
    json_object_set_string(result, "permissions", guild_member->permissions);
    json_object_set_string(result, "communication_disabled_until", guild_member->communication_disabled_until);

    return json_object_get_wrapping_value(result);
}
JSON_Value *struct_guild_widget(guild_widget_t *guild_widget) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    json_object_set_boolean(result, "enabled", guild_widget->enabled);
    json_object_set_string(result, "channel_id", guild_widget->channel_id);

    return json_object_get_wrapping_value(result);
}
JSON_Value *struct_guild_preview(guild_preview_t *guild_preview) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    json_object_set_string(result, "id", guild_preview->id);
    json_object_set_string(result, "name", guild_preview->name);
    json_object_set_string(result, "icon", guild_preview->icon);
    json_object_set_string(result, "splash", guild_preview->splash);
    json_object_set_string(result, "discovery_splash", guild_preview->discovery_splash);

    JSON_Array *emojis = yadl_json_array_builder(NULL);
    for (int i=0; i<guild_preview->emojis->size; i++)
        json_array_append_value(emojis, struct_emoji((emoji_t *)guild_preview->emojis->array[i]));

    json_object_set_string(result, "features", guild_preview->features);
    json_object_set_number(result, "approximate_member_count", guild_preview->approximate_member_count);
    json_object_set_number(result, "approximate_presence_count", guild_preview->approximate_presence_count);
    json_object_set_string(result, "description", guild_preview->description);

    return json_object_get_wrapping_value(result);
}
JSON_Value *struct_guild(guild_t *guild) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    json_object_set_string(result, "id", guild->id);
    json_object_set_string(result, "name", guild->name);
    json_object_set_string(result, "icon", guild->icon);
    json_object_set_string(result, "icon_hash", guild->icon_hash);
    json_object_set_string(result, "splash", guild->splash);
    json_object_set_string(result, "discovery_splash", guild->discovery_splash);
    json_object_set_boolean(result, "owner", guild->owner);
    json_object_set_string(result, "owner_id", guild->owner_id);
    json_object_set_string(result, "permissions", guild->permissions);
    json_object_set_string(result, "region", guild->region);
    json_object_set_string(result, "afk_channel_id", guild->afk_channel_id);
    json_object_set_number(result, "afk_timeout", guild->afk_timeout);
    json_object_set_boolean(result, "widget_enabled", guild->widget_enabled);
    json_object_set_string(result, "widget_channel_id", guild->widget_channel_id);
    json_object_set_number(result, "verification_level", guild->verification_level);
    json_object_set_number(result, "default_message_notifications", guild->default_message_notifications);
    json_object_set_number(result, "explicit_content_filter", guild->explicit_content_filter);
    json_object_set_string(result, "roles", guild->roles);

    JSON_Array *emojis = yadl_json_array_builder(NULL);
    for (int i=0; i<guild->emojis->size; i++)
        json_array_append_value(emojis, struct_emoji((emoji_t *)guild->emojis->array[i]));

    json_object_set_string(result, "features", guild->features);
    json_object_set_number(result, "mfa_level", guild->mfa_level);
    json_object_set_string(result, "application_id", guild->application_id);
    json_object_set_string(result, "system_channel_id", guild->system_channel_id);
    json_object_set_number(result, "system_channel_flags", guild->system_channel_flags);
    json_object_set_string(result, "rules_channel_id", guild->rules_channel_id);
    json_object_set_string(result, "joined_at", guild->joined_at);
    json_object_set_boolean(result, "large", guild->large);
    json_object_set_boolean(result, "unavailable", guild->unavailable);
    json_object_set_number(result, "member_count", guild->member_count);

    JSON_Array *voice_states = yadl_json_array_builder(NULL);
    for (int i=0; i<guild->voice_states->size; i++)
        json_array_append_value(voice_states, struct_voice_state((voice_state_t *)guild->voice_states->array[i]));


    JSON_Array *members = yadl_json_array_builder(NULL);
    for (int i=0; i<guild->members->size; i++)
        json_array_append_value(members, struct_guild_member((guild_member_t *)guild->members->array[i]));


    JSON_Array *channels = yadl_json_array_builder(NULL);
    for (int i=0; i<guild->channels->size; i++)
        json_array_append_value(channels, struct_channel((channel_t *)guild->channels->array[i]));

    json_object_set_string(result, "threads", guild->threads);
    json_object_set_string(result, "presences", guild->presences);
    json_object_set_number(result, "max_presences", guild->max_presences);
    json_object_set_number(result, "max_members", guild->max_members);
    json_object_set_string(result, "vanity_url_code", guild->vanity_url_code);
    json_object_set_string(result, "description", guild->description);
    json_object_set_string(result, "banner", guild->banner);
    json_object_set_number(result, "premium_tier", guild->premium_tier);
    json_object_set_number(result, "premium_subscription_count", guild->premium_subscription_count);
    json_object_set_string(result, "preferred_locale", guild->preferred_locale);
    json_object_set_string(result, "public_updates_channel_id", guild->public_updates_channel_id);
    json_object_set_number(result, "max_video_channel_users", guild->max_video_channel_users);
    json_object_set_number(result, "approximate_member_count", guild->approximate_member_count);
    json_object_set_number(result, "approximate_presence_count", guild->approximate_presence_count);
    json_object_set_value(result, "welcome_screen", struct_welcome_screen(guild->welcome_screen));
    json_object_set_number(result, "nsfw_level", guild->nsfw_level);
    json_object_set_string(result, "stage_instances", guild->stage_instances);

    JSON_Array *stickers = yadl_json_array_builder(NULL);
    for (int i=0; i<guild->stickers->size; i++)
        json_array_append_value(stickers, struct_sticker((sticker_t *)guild->stickers->array[i]));


    JSON_Array *guild_scheduled_events = yadl_json_array_builder(NULL);
    for (int i=0; i<guild->guild_scheduled_events->size; i++)
        json_array_append_value(guild_scheduled_events, struct_guild_scheduled_event((guild_scheduled_event_t *)guild->guild_scheduled_events->array[i]));

    json_object_set_boolean(result, "premium_progress_bar_enabled", guild->premium_progress_bar_enabled);

    return json_object_get_wrapping_value(result);
}
