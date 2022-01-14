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

#ifndef YADL_CALLBACK_H
#define YADL_CALLBACK_H

#include <stdint.h>
#include "../impl/impl.h"
#include "../impl/user.h"
#include "../impl/guild.h"
#include "../impl/message.h"
#include "../impl/channel.h"

typedef struct yadl_context yadl_context_t;

typedef struct yadl_object_metadata yadl_object_metadata_t;

struct yadl_event_on_ready {
    yadl_context_t *context;

    int8_t gateway_version;
    self_user_t *self_user;
    u_int16_t unavailable_guild_count;
};

typedef void (*yadl_event_on_ready_t)(const struct yadl_event_on_ready *event);

struct yadl_event_on_guild_create {
    yadl_context_t *context;

    guild_t *guild;
};

typedef void (*yadl_event_on_guild_create_t)(const struct yadl_event_on_guild_create *event);

struct yadl_event_on_direct_message_create {
    yadl_context_t *context;

    char* message_id;
    user_t *author;
    message_t *message;
    channel_t *channel;
};

typedef void (*yadl_event_on_direct_message_create_t)(const struct yadl_event_on_direct_message_create *event);

struct yadl_event_on_guild_message_create {
    yadl_context_t *context;

    char* message_id;
    user_t *author;
    guild_member_t *member;
    message_t *message;
    channel_t *channel;
    guild_t *guild;
    bool is_webhook_message;
};

typedef void (*yadl_event_on_guild_message_create_t)(const struct yadl_event_on_guild_message_create *event);

typedef struct __attribute__((__packed__)) {
    yadl_event_on_ready_t on_ready;
    yadl_event_on_direct_message_create_t on_direct_message_create;

    yadl_event_on_guild_create_t on_guild_create;
    yadl_event_on_guild_message_create_t on_guild_message_create;
} yadl_event_cb_t;

yadl_object_metadata_t *yadl_get_object_metadata(size_t type);

#endif //YADL_CALLBACK_H
