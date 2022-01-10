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

#include <parson.h>
#include <stdbool.h>
#include "../utils/utils.h"
#include "../json/json.h"

#ifndef YADL_USER_H
#define YADL_USER_H

#define YADL_USER_AVATAR "/avatars/%s/%s.png"

typedef struct __attribute__((__packed__)) {
    char *id;
    char *username;
    char *discriminator;
    char *avatar;
    bool bot;
    bool system;
    bool mfa_enabled;
    char *banner;
    int accent_color;
    char *locale;
    bool verified;
    char *email;
    int flags;
    int premium_type;
    int public_flags;

} yadl_user;

typedef yadl_user user_t;
typedef yadl_user self_user_t;

user_t *parse_user(JSON_Value *user_value);

#endif //YADL_USER_H
