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

#ifndef YADL_GUILD_H
#define YADL_GUILD_H

#include <stdbool.h>
#include <stdint.h>
#include "parson.h"
#include "../utils/utils.h"
#include "../json/json.h"
#include "user.h"

typedef struct yadl_object_array yadl_object_array_t;

typedef struct __attribute__((__packed__)) {
    char *channel_id;
    char *description;
    char *emoji_id;
    char *emoji_name;

} welcome_screen_channel_t;

typedef struct __attribute__((__packed__)) {
    char *description;
    yadl_object_array_t *welcome_channels;
    /* array of welcome screen channel objects */

} welcome_screen_t;

typedef struct __attribute__((__packed__)) {
    char *id;
    char *name;
    char *icon;
    char *icon_hash;
    char *splash;
    char *discovery_splash;
    bool owner;
    char *owner_id;
    char *permissions;
    char *region;
    char *afk_channel_id;
    int afk_timeout;
    bool widget_enabled;
    char *widget_channel_id;
    int verification_level;
    int default_message_notifications;
    int explicit_content_filter;
    char *roles;
    /* array of role objects */
    yadl_object_array_t *emojis;
    /* array of emoji objects */
    char *features;
    /* array of guild feature strings */
    int mfa_level;
    char *application_id;
    char *system_channel_id;
    int system_channel_flags;
    char *rules_channel_id;
    char *joined_at;
    bool large;
    bool unavailable;
    int member_count;
    yadl_object_array_t *voice_states;
    /* array of partial voice state objects */
    yadl_object_array_t *members;
    /* array of guild member objects */
    yadl_object_array_t *channels;
    /* array of channel objects */
    char *threads;
    /* array of channel objects */
    char *presences;
    /* array of partial presence update objects */
    int max_presences;
    int max_members;
    char *vanity_url_code;
    char *description;
    char *banner;
    int premium_tier;
    int premium_subscription_count;
    char *preferred_locale;
    char *public_updates_channel_id;
    int max_video_channel_users;
    int approximate_member_count;
    int approximate_presence_count;
    welcome_screen_t *welcome_screen;
    /* welcome screen object */
    int nsfw_level;
    char *stage_instances;
    /* array of stage instance objects */
    yadl_object_array_t *stickers;
    /* array of sticker objects */
    yadl_object_array_t *guild_scheduled_events;
    /* array of guild scheduled event objects */
    bool premium_progress_bar_enabled;

} guild_t;

typedef struct __attribute__((__packed__)) {
    char *code;
    char *name;
    char *description;
    int usage_count;
    char *creator_id;
    user_t *creator;
    /* user object */
    char *created_at;
    char *updated_at;
    char *source_guild_id;
    guild_t *serialized_source_guild;
    /* partial guild object */
    bool is_dirty;

} guild_template_t;

typedef struct __attribute__((__packed__)) {
    user_t *user;
    /* user object */
    char *nick;
    char *avatar;
    char *roles;
    /* array of snowflakes */
    char *joined_at;
    char *premium_since;
    bool deaf;
    bool mute;
    bool pending;
    char *permissions;
    char *communication_disabled_until;

} guild_member_t;

typedef struct __attribute__((__packed__)) {
    char *guild_scheduled_event_id;
    user_t *user;
    /* user */
    guild_member_t *member;
    /* guild member */

} guild_scheduled_event_user_t;

typedef struct __attribute__((__packed__)) {
    char *id;
    char *guild_id;
    char *channel_id;
    char *creator_id;
    char *name;
    char *description;
    char *scheduled_start_time;
    char *scheduled_end_time;
    char *privacy_level;
    /* privacy level */
    char *status;
    /* event status */
    char *entity_type;
    /* scheduled entity type */
    char *entity_id;
    char *entity_metadata;
    /* entity metadata */
    user_t *creator;
    /* user object */
    int user_count;

} guild_scheduled_event_t;

typedef struct __attribute__((__packed__)) {
    char *reason;
    user_t *user;
    /* user object */

} ban_t;

typedef struct __attribute__((__packed__)) {
    bool enabled;
    char *channel_id;

} guild_widget_t;

typedef struct __attribute__((__packed__)) {
    char *id;
    char *name;
    char *icon;
    char *splash;
    char *discovery_splash;
    yadl_object_array_t *emojis;
    /* array of emoji objects */
    char *features;
    /* array of guild feature strings */
    int approximate_member_count;
    int approximate_presence_count;
    char *description;

} guild_preview_t;

guild_t *parse_guild(JSON_Value *guild_value);

guild_preview_t *parse_guild_preview(JSON_Value *guild_preview_value);

guild_widget_t *parse_guild_widget(JSON_Value *guild_widget_value);

guild_member_t *parse_guild_member(JSON_Value *guild_member_value);

ban_t *parse_ban(JSON_Value *ban_value);

welcome_screen_t *parse_welcome_screen(JSON_Value *welcome_screen_value);

welcome_screen_channel_t *parse_welcome_screen_channel(JSON_Value *welcome_screen_channel_value);

guild_scheduled_event_t *parse_guild_scheduled_event(JSON_Value *guild_scheduled_event_value);

guild_scheduled_event_user_t *parse_guild_scheduled_event_user(JSON_Value *guild_scheduled_event_user_value);

guild_template_t *parse_guild_template(JSON_Value *guild_template_value);

JSON_Value *struct_guild_template(guild_template_t *guild_template);

JSON_Value *struct_guild_scheduled_event_user(guild_scheduled_event_user_t *guild_scheduled_event_user);

JSON_Value *struct_guild_scheduled_event(guild_scheduled_event_t *guild_scheduled_event);

JSON_Value *struct_welcome_screen_channel(welcome_screen_channel_t *welcome_screen_channel);

JSON_Value *struct_welcome_screen(welcome_screen_t *welcome_screen);

JSON_Value *struct_ban(ban_t *ban);

JSON_Value *struct_guild_member(guild_member_t *guild_member);

JSON_Value *struct_guild_widget(guild_widget_t *guild_widget);

JSON_Value *struct_guild_preview(guild_preview_t *guild_preview);

JSON_Value *struct_guild(guild_t *guild);



#endif //YADL_GUILD_H
