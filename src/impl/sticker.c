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

#include "sticker.h"

sticker_t *parse_sticker(JSON_Value *sticker_value) {
    JSON_Object *sticker = json_object(sticker_value);
    sticker_t *result = yadl_malloc(sizeof(sticker_t), true);

    *result = (sticker_t) {(char *) json_object_get_string(sticker, "id"),
                           (char *) json_object_get_string(sticker, "pack_id"),
                           (char *) json_object_get_string(sticker, "name"),
                           (char *) json_object_get_string(sticker, "description"),
                           (char *) json_object_get_string(sticker, "tags"),
                           (char *) json_object_get_string(sticker, "asset"),
                           (int) json_object_get_number(sticker, "type"),
                           (int) json_object_get_number(sticker, "format_type"),
                           yadl_json_boolean_null_check(json_object_get_boolean(sticker, "available")),
                           (char *) json_object_get_string(sticker, "guild_id"),
                           (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(sticker, "user"))),
                           (int) json_object_get_number(sticker, "sort_value")
    };

    return result;
}



sticker_item_t *parse_sticker_item(JSON_Value *sticker_item_value) {
    JSON_Object *sticker_item = json_object(sticker_item_value);
    sticker_item_t *result = yadl_malloc(sizeof(sticker_item_t), true);

    *result = (sticker_item_t) {(char *) json_object_get_string(sticker_item, "id"),
                                (char *) json_object_get_string(sticker_item, "name"),
                                (int) json_object_get_number(sticker_item, "format_type")
    };

    return result;
}



sticker_pack_t *parse_sticker_pack(JSON_Value *sticker_pack_value) {
    JSON_Object *sticker_pack = json_object(sticker_pack_value);
    sticker_pack_t *result = yadl_malloc(sizeof(sticker_pack_t), true);

    *result = (sticker_pack_t) {(char *) json_object_get_string(sticker_pack, "id"),
                                (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(sticker_pack, "stickers"))),
                                (char *) json_object_get_string(sticker_pack, "name"),
                                (char *) json_object_get_string(sticker_pack, "sku_id"),
                                (char *) json_object_get_string(sticker_pack, "cover_sticker_id"),
                                (char *) json_object_get_string(sticker_pack, "description"),
                                (char *) json_object_get_string(sticker_pack, "banner_asset_id")
    };

    return result;
}
