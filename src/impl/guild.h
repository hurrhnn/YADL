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

typedef struct yadl_guild {
    char *id;
    char *name;
    char *icon;
    char *splash;
    char *discovery_splash;
    bool owner;
    char *owner_id;
    char *permissions;
    char *afk_channel_id;
    int32_t afk_timeout;
    bool widget_enabled;
    char *widget_channel_id;
    int8_t verification_level;
    int8_t default_message_notifications;
    int8_t explicit_content_filter;

    char *roles, *emojis, *features;
    /* roles, emojis, features object */

    int8_t mfa_level;
    char *application_id;
    char *system_channel_id;
    int8_t system_channel_flags;
    char* rules_channel_id;
    char* joined_at;
    bool large;
    bool unavailable;
    int32_t member_count;

    char *voice_states, *members, *channels, *threads, *presences;
    /* voice_states, members, channels, threads, presences object */

    int32_t max_members;
    char *vanity_url_code;
    char *description;
    char *banner;
    int8_t premium_tier;
    int32_t premium_subscription_count;
    char *preferred_locale;
    char *public_updates_channel_id;
    int32_t max_video_channel_users;
    int32_t approximate_member_count;
    int32_t approximate_presence_count;

    char *welcome_screen;
    /* welcome_screen object */

    int8_t nsfw_level;

    char *stage_instances, *stickers, *guild_scheduled_events;
    /* stage_instances, stickers, guild_scheduled_events */

    bool premium_progress_bar_enabled;
}guild_t;

guild_t *parse_guild(JSON_Value *guild_value);

#endif //YADL_GUILD_H
