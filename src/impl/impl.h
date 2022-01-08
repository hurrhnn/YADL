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

#include "callback.h"
#include "guild.h"
#include "linked_list.h"
#include "user.h"

#ifndef YADL_IMPL_H
#define YADL_IMPL_H

#define YADL_GATEWAY_INTENTS_DEFAULT 32509

enum YADL_GATEWAY_INTENTS {
    GUILDS                    = (1 << 0),
    GUILD_MEMBERS             = (1 << 1),
    GUILD_BANS                = (1 << 2),
    GUILD_EMOJIS_AND_STICKERS = (1 << 3),
    GUILD_INTEGRATIONS        = (1 << 4),
    GUILD_WEBHOOKS            = (1 << 5),
    GUILD_INVITES             = (1 << 6),
    GUILD_VOICE_STATES        = (1 << 7),
    GUILD_PRESENCES           = (1 << 8),
    GUILD_MESSAGES            = (1 << 9),
    GUILD_MESSAGE_REACTIONS   = (1 << 10),
    GUILD_MESSAGE_TYPING      = (1 << 11),
    DIRECT_MESSAGES           = (1 << 12),
    DIRECT_MESSAGE_REACTIONS  = (1 << 13),
    DIRECT_MESSAGE_TYPING     = (1 << 14)
} YADL_GATEWAY_INTENTS;

#define YADL_GATEWAY_INTENTS_ALL 32767

#endif //YADL_IMPL_H
