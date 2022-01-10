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
#include "../utils/utils.h"

typedef struct yadl_application {
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
    char *owner;
    /* partial user object */
    char *summary;
    char *verify_key;
    char *team;
    /* team object */
    char *guild_id;
    char *primary_sku_id;
    char *slug;
    char *cover_image;
    int flags;

} application_t;

#endif //YADL_APPLICATION_H
