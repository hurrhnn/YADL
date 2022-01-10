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

#ifndef YADL_INTEGRATION_H
#define YADL_INTEGRATION_H

#include <stdbool.h>
#include "parson.h"
#include "../utils/utils.h"
#include "../json/json.h"

typedef struct __attribute__((__packed__)) {
    char *id;
    char *name;
    char *type;
    bool enabled;
    bool syncing;
    char *role_id;
    bool enable_emoticons;
    char *expire_behavior;
    /* integration expire behavior */
    int expire_grace_period;
    char *user;
    /* user object */
    char *account;
    /* account object */
    char *synced_at;
    int subscriber_count;
    bool revoked;
    char *application;
    /* application object */

} integration_t;

typedef struct __attribute__((__packed__)) {
    char *id;
    char *name;

} integration_account_t;

typedef struct __attribute__((__packed__)) {
    char *id;
    char *name;
    char *icon;
    char *description;
    char *summary;
    char *bot;
    /* user object */

} integration_application_t;

integration_t *parse_integration(JSON_Value *integration_value);

integration_account_t *parse_integration_account(JSON_Value *integration_account_value);

integration_application_t *parse_integration_application(JSON_Value *integration_application_value);

#endif //YADL_INTEGRATION_H
