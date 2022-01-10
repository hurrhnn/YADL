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

#ifndef YADL_IMPL_H
#define YADL_IMPL_H

#include "../callback/callback.h"
#include "guild.h"
#include "linked_list.h"
#include "user.h"
#include "application.h"
#include "audit_log.h"
#include "embed.h"
#include "channel.h"
#include "message.h"
#include "reaction.h"
#include "thread.h"
#include "attachment.h"
#include "emoji.h"
#include "integration.h"
#include "sticker.h"
#include "invite.h"
#include "voice.h"
#include "webhook.h"

#define YADL_OBJECT_APPLICATION 0
#define YADL_OBJECT_AUDIT_LOG 1
#define YADL_OBJECT_AUDIT_LOG_ENTRY 2
#define YADL_OBJECT_AUDIT_LOG_CHANGE 3
#define YADL_OBJECT_CHANNEL 4
#define YADL_OBJECT_MESSAGE 5
#define YADL_OBJECT_MESSAGE_ACTIVITY 6
#define YADL_OBJECT_MESSAGE_REFERENCE 7
#define YADL_OBJECT_FOLLOWED_CHANNEL 8
#define YADL_OBJECT_REACTION 9
#define YADL_OBJECT_OVERWRITE 10
#define YADL_OBJECT_THREAD_METADATA 11
#define YADL_OBJECT_THREAD_MEMBER 12
#define YADL_OBJECT_EMBED 13
#define YADL_OBJECT_EMBED_THUMBNAIL 14
#define YADL_OBJECT_EMBED_VIDEO 15
#define YADL_OBJECT_EMBED_IMAGE 16
#define YADL_OBJECT_EMBED_PROVIDER 17
#define YADL_OBJECT_EMBED_AUTHOR 18
#define YADL_OBJECT_EMBED_FOOTER 19
#define YADL_OBJECT_EMBED_FIELD 20
#define YADL_OBJECT_ATTACHMENT 21
#define YADL_OBJECT_CHANNEL_MENTION 22
#define YADL_OBJECT_ALLOWED_MENTIONS 23
#define YADL_OBJECT_EMOJI 24
#define YADL_OBJECT_GUILD 25
#define YADL_OBJECT_GUILD_PREVIEW 26
#define YADL_OBJECT_GUILD_WIDGET 27
#define YADL_OBJECT_GUILD_MEMBER 28
#define YADL_OBJECT_INTEGRATION 29
#define YADL_OBJECT_INTEGRATION_ACCOUNT 30
#define YADL_OBJECT_INTEGRATION_APPLICATION 31
#define YADL_OBJECT_BAN 32
#define YADL_OBJECT_WELCOME_SCREEN 33
#define YADL_OBJECT_WELCOME_SCREEN_CHANNEL 34
#define YADL_OBJECT_GUILD_SCHEDULED_EVENT 35
#define YADL_OBJECT_GUILD_SCHEDULED_EVENT_USER 36
#define YADL_OBJECT_GUILD_TEMPLATE 37
#define YADL_OBJECT_INVITE 38
#define YADL_OBJECT_INVITE_METADATA 39
#define YADL_OBJECT_INVITE_STAGE_INSTANCE 40
#define YADL_OBJECT_STAGE_INSTANCE 41
#define YADL_OBJECT_STICKER 42
#define YADL_OBJECT_STICKER_ITEM 43
#define YADL_OBJECT_STICKER_PACK 44
#define YADL_OBJECT_RESPONSE 45
#define YADL_OBJECT_USER 46
#define YADL_OBJECT_CONNECTION 47
#define YADL_OBJECT_VOICE_STATE 48
#define YADL_OBJECT_VOICE_REGION 49
#define YADL_OBJECT_WEBHOOK 50

typedef struct {
    size_t type;
    char member_size[YADL_MIDIUM_SIZE];
} yadl_object_metadata_t;

yadl_object_metadata_t *yadl_get_object_metadata(size_t type);

typedef union {
    struct {
        u_int8_t GUILDS                    : 1;
        u_int8_t GUILD_MEMBERS             : 1;
        u_int8_t GUILD_BANS                : 1;
        u_int8_t GUILD_EMOJIS_AND_STICKERS : 1;
        u_int8_t GUILD_INTEGRATIONS        : 1;
        u_int8_t GUILD_WEBHOOKS            : 1;
        u_int8_t GUILD_INVITES             : 1;
        u_int8_t GUILD_VOICE_STATES        : 1;
        u_int8_t GUILD_PRESENCES           : 1;
        u_int8_t GUILD_MESSAGES            : 1;
        u_int8_t GUILD_MESSAGE_REACTIONS   : 1;
        u_int8_t GUILD_MESSAGE_TYPING      : 1;
        u_int8_t DIRECT_MESSAGES           : 1;
        u_int8_t DIRECT_MESSAGE_REACTIONS  : 1;
        u_int8_t DIRECT_MESSAGE_TYPING     : 1;
    } flags;
    u_int16_t value;
} yadl_gateway_intents;

#define YADL_GATEWAY_INTENTS_DEFAULT 32509
#define YADL_GATEWAY_INTENTS_ALL 32767

#endif //YADL_IMPL_H
