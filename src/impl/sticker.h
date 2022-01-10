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

#ifndef YADL_STICKER_H
#define YADL_STICKER_H

#include <stdbool.h>
#include "parson.h"
#include "../utils/utils.h"

typedef struct yadl_sticker {
    char *id;
    char *pack_id;
    char *name;
    char *description;
    char *tags;
    char *asset;
    int type;
    int format_type;
    bool available;
    char *guild_id;
    char *user;
    /* user object */
    int sort_value;

} sticker_t;

typedef struct yadl_sticker_item {
    char *id;
    char *name;
    int format_type;

} sticker_item_t;

typedef struct yadl_sticker_pack {
    char *id;
    char *stickers;
    /* array of sticker objects */
    char *name;
    char *sku_id;
    char *cover_sticker_id;
    char *description;
    char *banner_asset_id;

} sticker_pack_t;

#endif //YADL_STICKER_H
