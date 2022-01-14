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

#ifndef YADL_REACTION_H
#define YADL_REACTION_H

#include <stdbool.h>
#include "parson.h"
#include "../utils/utils.h"
#include "../json/json.h"
#include "emoji.h"

typedef struct __attribute__((__packed__)) {
    int count;
    bool me;
    emoji_t *emoji;
    /* partial emoji object */

} reaction_t;

reaction_t *parse_reaction(JSON_Value *reaction_value);

JSON_Value *struct_reaction(reaction_t *reaction);

#endif //YADL_REACTION_H
