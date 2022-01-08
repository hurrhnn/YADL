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
#include "user.h"
#include "guild.h"

struct yadl_event_on_ready {
    int8_t gateway_version;
    self_user_t *self_user;
    u_int16_t unavailable_guild_count;
};

typedef void (*yadl_event_on_ready_t)(const struct yadl_event_on_ready *event, void *user_data);

struct yadl_event_on_guild_create {
    guild_t *guild;
};

typedef void (*yadl_event_on_guild_create_t)(const struct yadl_event_on_guild_create *event, void *user_data);

typedef struct yadl_event_cb {
    yadl_event_on_ready_t on_ready;
    yadl_event_on_guild_create_t on_guild_create;
    void *user_data;
} yadl_event_cb_t;

#endif //YADL_CALLBACK_H
