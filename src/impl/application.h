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

#ifndef YADL_APPLICATION_H
#define YADL_APPLICATION_H

#include <stdbool.h>
#include "parson.h"
#include "user.h"
#include "../utils/utils.h"
#include "../json/json.h"

typedef struct yadl_object_array yadl_object_array_t;

typedef union {
    struct {
        u_int16_t UNUSED_BLANK                    : 12;
        u_int8_t GATEWAY_PRESENCE                 : 1;
        u_int8_t GATEWAY_PRESENCE_LIMITED         : 1;
        u_int8_t GATEWAY_GUILD_MEMBERS            : 1;
        u_int8_t GATEWAY_GUILD_MEMBERS_LIMITED    : 1;
        u_int8_t VERIFICATION_PENDING_GUILD_LIMIT : 1;
        u_int8_t EMBEDDED                         : 1;
        u_int8_t GATEWAY_MESSAGE_CONTENT          : 1;
        u_int8_t GATEWAY_MESSAGE_CONTENT_LIMITED  : 1;
    } flags;
    u_int32_t value;
} yadl_application_flags_t;

typedef struct __attribute__((__packed__)) {
    int membership_state;
    char* team_id;
    user_t *user;
} team_member_t;

typedef struct __attribute__((__packed__)) {
    char* icon;
    char* id;
    yadl_object_array_t *members;
    char* name;
    char* owner_user_id;
} team_t;

typedef struct __attribute__((__packed__)) {
    char *id;
    char *name;
    char *icon;
    char *description;
    char *rpc_origins;
    /* array of strings */

    bool bot_public;
    bool bot_require_code_grant;
    char *terms_of_service_url;
    char *privacy_policy_url;
    user_t *owner;
    /* partial user object */

    char *summary;
    char *verify_key;
    team_t *team;
    /* team object */

    char *guild_id;
    char *primary_sku_id;
    char *slug;
    char *cover_image;
    int flags;

} application_t;

application_t *parse_application(JSON_Value *application_value);

team_t *parse_team(JSON_Value *team_value);

team_member_t *parse_team_member(JSON_Value *team_member_value);

JSON_Value *struct_team_member(team_member_t *team_member);

JSON_Value *struct_team(team_t *team);

JSON_Value *struct_application(application_t *application);

#endif //YADL_APPLICATION_H
