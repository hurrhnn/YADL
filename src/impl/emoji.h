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

#ifndef YADL_EMOJI_H
#define YADL_EMOJI_H

#include <stdbool.h>
#include <parson.h>
#include "../utils/utils.h"
#include "../json/json.h"
#include "user.h"

typedef struct __attribute__((__packed__)) {
    char *id;
    char *name;
    char *roles;
    /* array of role object ids */
    user_t *user;
    /* user object */
    bool require_colons;
    bool managed;
    bool animated;
    bool available;

} emoji_t;

emoji_t *parse_emoji(JSON_Value *emoji_value);

JSON_Value *struct_emoji(emoji_t *emoji);

#endif //YADL_EMOJI_H
