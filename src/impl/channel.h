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

#include <stdbool.h>
#include "parson.h"
#include "../utils/utils.h"

typedef struct yadl_channel {
    char *id;
    int type;
    char *guild_id;
    int position;
    char *permission_overwrites;
    /* array of overwrite objects */
    char *name;
    char *topic;
    bool nsfw;
    char *last_message_id;
    int bitrate;
    int user_limit;
    int rate_limit_per_user;
    char *recipients;
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
    char *member;
    /* a thread member object */
    int default_auto_archive_duration;
    char *permissions;

} channel_t;

typedef struct yadl_channel_mention {
    char *id;
    char *guild_id;
    int type;
    char *name;

} channel_mention_t;

typedef struct yadl_allowed_mentions {
    char *parse;
    /* array of allowed mention types */
    char *roles;
    /* list of snowflakes */
    char *users;
    /* list of snowflakes */
    bool replied_user;

} allowed_mentions_t;

channel_t *parse_channel(JSON_Value *channel_value);

channel_mention_t *parse_channel_mention(JSON_Value *channel_mention_value);

allowed_mentions_t *parse_allowed_mentions(JSON_Value *allowed_mentions_value);

#endif //YADL_CHANNEL_H
