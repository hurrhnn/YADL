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

#ifndef YADL_INVITE_H
#define YADL_INVITE_H

#include <stdbool.h>
#include <parson.h>
#include <yadl/utils/utils.h>
#include <yadl/json/json.h>
#include <yadl/impl/guild.h>
#include <yadl/impl/channel.h>
#include <yadl/impl/application.h>

typedef struct __attribute__((__packed__)) {
    char *members;
    /* array of partial guild member objects */
    int participant_count;
    int speaker_count;
    char *topic;

} invite_stage_instance_t;

typedef struct __attribute__((__packed__)) {
    char *code;
    guild_t *guild;
    /* partial guild object */
    channel_t *channel;
    /* partial channel object */
    user_t *inviter;
    /* user object */
    int target_type;
    user_t *target_user;
    /* user object */
    application_t *target_application;
    /* partial application object */
    int approximate_presence_count;
    int approximate_member_count;
    char *expires_at;
    invite_stage_instance_t *stage_instance;
    /* invite stage instance object */
    guild_scheduled_event_t *guild_scheduled_event;
    /* guild scheduled event object */

} invite_t;

typedef struct __attribute__((__packed__)) {
    int uses;
    int max_uses;
    int max_age;
    bool temporary;
    char *created_at;

} invite_metadata_t;

typedef struct __attribute__((__packed__)) {
    char *id;
    char *guild_id;
    char *channel_id;
    char *topic;
    int privacy_level;
    bool discoverable_disabled;

} stage_instance_t;

invite_t *parse_invite(JSON_Value *invite_value);

invite_metadata_t *parse_invite_metadata(JSON_Value *invite_metadata_value);

invite_stage_instance_t *parse_invite_stage_instance(JSON_Value *invite_stage_instance_value);

stage_instance_t *parse_stage_instance(JSON_Value *stage_instance_value);

JSON_Value *struct_stage_instance(stage_instance_t *stage_instance);

JSON_Value *struct_invite_stage_instance(invite_stage_instance_t *invite_stage_instance);

JSON_Value *struct_invite_metadata(invite_metadata_t *invite_metadata);

JSON_Value *struct_invite(invite_t *invite);

#endif //YADL_INVITE_H
