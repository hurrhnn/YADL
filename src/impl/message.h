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
#include "parson.h"
#include "../utils/utils.h"

typedef struct yadl_message {
    char *channel_id;
    char *guild_id;
    char *author;
    /* user object */
    char *member;
    /* partial guild member object */
    char *content;
    char *timestamp;
    char *edited_timestamp;
    bool tts;
    bool mention_everyone;
    char *mentions;
    /* array of user objects, with an additional partial member field */
    char *mention_roles;
    /* array of role object ids */
    char *mention_channels;
    /* array of channel mention objects */
    char *attachments;
    /* array of attachment objects */
    char *embeds;
    /* array of embed objects */
    char *reactions;
    /* array of reaction objects */
    char *nonce;
    bool pinned;
    char *webhook_id;
    int type;
    char *activity;
    /* message activity object */
    char *application;
    /* partial application object */
    char *application_id;
    char *message_reference;
    /* message reference object */
    int flags;
    char *referenced_message;
    /* message object */
    char *interaction;
    /* message interaction object */
    char *thread;
    /* channel object */
    char *components;
    /* Array of message components */
    char *sticker_items;
    /* array of message sticker item objects */
    char *stickers;
    /* array of sticker objects */

} message_t;

typedef struct yadl_message_activity {
    int type;
    char *party_id;

} message_activity_t;

typedef struct yadl_message_reference {
    char *message_id;
    char *channel_id;
    char *guild_id;
    bool fail_if_not_exists;

} message_reference_t;

typedef struct yadl_followed_channel {
    char *channel_id;
    char *webhook_id;

} followed_channel_t;

message_t *parse_message(JSON_Value *message_value);

message_activity_t *parse_message_activity(JSON_Value *message_activity_value);

message_reference_t *parse_message_reference(JSON_Value *message_reference_value);

followed_channel_t *parse_followed_channel(JSON_Value *followed_channel_value);

#endif //YADL_MESSAGE_H
