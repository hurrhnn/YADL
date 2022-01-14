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

#ifndef YADL_MESSAGE_H
#define YADL_MESSAGE_H

#include <stdbool.h>
#include <parson.h>
#include "../utils/utils.h"
#include "../json/json.h"
#include "user.h"
#include "guild.h"
#include "channel.h"
#include "application.h"
#include "integration.h"
#include "sticker.h"

typedef struct yadl_object_array yadl_object_array_t;

typedef struct __attribute__((__packed__)) {
    int type;
    char *party_id;

} message_activity_t;

typedef struct __attribute__((__packed__)) {
    char *message_id;
    char *channel_id;
    char *guild_id;
    bool fail_if_not_exists;

} message_reference_t;

typedef struct __attribute__((__packed__)) message {
    char* id;
    char *channel_id;
    char *guild_id;
    user_t *author;
    /* user object */
    guild_member_t *member;
    /* partial guild member object */
    char *content;
    char *timestamp;
    char *edited_timestamp;
    bool tts;
    bool mention_everyone;
    yadl_object_array_t *mentions;
    /* array of user objects, with an additional partial member field */
    char *mention_roles;
    /* array of role object ids */
    yadl_object_array_t *mention_channels;
    /* array of channel mention objects */
    yadl_object_array_t *attachments;
    /* array of attachment objects */
    yadl_object_array_t *embeds;
    /* array of embed objects */
    yadl_object_array_t *reactions;
    /* array of reaction objects */
    char *nonce;
    bool pinned;
    char *webhook_id;
    int type;
    char *activity;
    /* message activity object */
    application_t *application;
    /* partial application object */
    char *application_id;
    message_reference_t *message_reference;
    /* message reference object */
    int flags;
    struct message *referenced_message;
    /* message object */
    integration_t *interaction;
    /* message interaction object */
    channel_t *thread;
    /* channel object */
    char *components;
    /* Array of message components */
    yadl_object_array_t *sticker_items;
    /* array of message sticker item objects */
    yadl_object_array_t *stickers;
    /* array of sticker objects */

} message_t;

typedef struct __attribute__((__packed__)) {
    char *channel_id;
    char *webhook_id;

} followed_channel_t;

message_t *parse_message(JSON_Value *message_value);

message_activity_t *parse_message_activity(JSON_Value *message_activity_value);

message_reference_t *parse_message_reference(JSON_Value *message_reference_value);

followed_channel_t *parse_followed_channel(JSON_Value *followed_channel_value);

JSON_Value *struct_followed_channel(followed_channel_t *followed_channel);

JSON_Value *struct_message_reference(message_reference_t *message_reference);

JSON_Value *struct_message_activity(message_activity_t *message_activity);

JSON_Value *struct_message(message_t *message);

#endif //YADL_MESSAGE_H
