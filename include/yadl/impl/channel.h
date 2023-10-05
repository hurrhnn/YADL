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

#ifndef YADL_CHANNEL_H
#define YADL_CHANNEL_H

#define YADL_CHANNEL_GUILD_TEXT           0
#define YADL_CHANNEL_DM	                  1
#define YADL_CHANNEL_GUILD_VOICE          2
#define YADL_CHANNEL_GROUP_DM             3
#define YADL_CHANNEL_GUILD_CATEGORY	      4
#define YADL_CHANNEL_GUILD_NEWS	          5
#define YADL_CHANNEL_GUILD_STORE          6
#define YADL_CHANNEL_GUILD_NEWS_THREAD    10
#define YADL_CHANNEL_GUILD_PUBLIC_THREAD  11
#define YADL_CHANNEL_GUILD_PRIVATE_THREAD 12
#define YADL_CHANNEL_GUILD_STAGE_VOICE    13

#include <stdbool.h>
#include <parson.h>
#include <yadl/utils/utils.h>
#include <yadl/json/json.h>
#include <yadl/impl/guild.h>

typedef struct yadl_object_array yadl_object_array_t;

typedef struct __attribute__((__packed__)) {
    char *id;
    int type;
    char *guild_id;
    int position;
    yadl_object_array_t *permission_overwrites;
    /* array of overwrite objects */
    char *name;
    char *topic;
    bool nsfw;
    char *last_message_id;
    int bitrate;
    int user_limit;
    int rate_limit_per_user;
    yadl_object_array_t *recipients;
    /* array of user objects */
    char *icon;
    char *owner_id;
    char *application_id;
    char *parent_id;
    char *last_pin_timestamp;
    char *rtc_region;
    int video_quality_mode;
    int message_count;
    int member_count;
    char *thread_metadata;
    /* a thread metadata object */
    guild_member_t *member;
    /* a thread member object */
    int default_auto_archive_duration;
    char *permissions;

} channel_t;

typedef struct __attribute__((__packed__)) {
    char *id;
    char *guild_id;
    int type;
    char *name;

} channel_mention_t;

typedef struct __attribute__((__packed__)) {
    char *parse;
    /* array of allowed mention types */
    char *roles;
    /* list of snowflakes */
    char *users;
    /* list of snowflakes */
    bool replied_user;

} allowed_mentions_t;

typedef struct __attribute__((__packed__)) {
    char *id;
    int type;
    char *allow;
    char *deny;

} overwrite_t;

channel_t *parse_channel(JSON_Value *channel_value);

channel_mention_t *parse_channel_mention(JSON_Value *channel_mention_value);

allowed_mentions_t *parse_allowed_mentions(JSON_Value *allowed_mentions_value);

overwrite_t *parse_overwrite(JSON_Value *overwrite_value);

JSON_Value *struct_overwrite(overwrite_t *overwrite);

JSON_Value *struct_allowed_mentions(allowed_mentions_t *allowed_mentions);

JSON_Value *struct_channel_mention(channel_mention_t *channel_mention);

JSON_Value *struct_channel(channel_t *channel);

#endif //YADL_CHANNEL_H
