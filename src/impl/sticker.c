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

#include <yadl/impl/sticker.h>
#include <yadl/impl/impl.h>

sticker_t *parse_sticker(JSON_Value *sticker_value) {
    JSON_Object *sticker = json_object(sticker_value);
    sticker_t *result = yadl_malloc(sizeof(sticker_t));

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
                           parse_user(json_object_get_wrapping_value(json_object_get_object(sticker, "user"))),
                           (int) json_object_get_number(sticker, "sort_value")
    };

    return result;
}

sticker_item_t *parse_sticker_item(JSON_Value *sticker_item_value) {
    JSON_Object *sticker_item = json_object(sticker_item_value);
    sticker_item_t *result = yadl_malloc(sizeof(sticker_item_t));

    *result = (sticker_item_t) {(char *) json_object_get_string(sticker_item, "id"),
                                (char *) json_object_get_string(sticker_item, "name"),
                                (int) json_object_get_number(sticker_item, "format_type")
    };

    return result;
}

sticker_pack_t *parse_sticker_pack(JSON_Value *sticker_pack_value) {
    JSON_Object *sticker_pack = json_object(sticker_pack_value);
    sticker_pack_t *result = yadl_malloc(sizeof(sticker_pack_t));

    *result = (sticker_pack_t) {(char *) json_object_get_string(sticker_pack, "id"),
                                yadl_object_array_parse(YADL_OBJECT_STICKER, json_object_get_array(sticker_pack, "stickers")),
                                (char *) json_object_get_string(sticker_pack, "name"),
                                (char *) json_object_get_string(sticker_pack, "sku_id"),
                                (char *) json_object_get_string(sticker_pack, "cover_sticker_id"),
                                (char *) json_object_get_string(sticker_pack, "description"),
                                (char *) json_object_get_string(sticker_pack, "banner_asset_id")
    };

    return result;
}

JSON_Value *struct_sticker_pack(sticker_pack_t *sticker_pack) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    json_object_set_string(result, "id", sticker_pack->id);

    JSON_Array *stickers = yadl_json_array_builder(NULL);
    for (int i=0; i<sticker_pack->stickers->size; i++)
        json_array_append_value(stickers, struct_sticker((sticker_t *)sticker_pack->stickers->array[i]));

    json_object_set_string(result, "name", sticker_pack->name);
    json_object_set_string(result, "sku_id", sticker_pack->sku_id);
    json_object_set_string(result, "cover_sticker_id", sticker_pack->cover_sticker_id);
    json_object_set_string(result, "description", sticker_pack->description);
    json_object_set_string(result, "banner_asset_id", sticker_pack->banner_asset_id);

    return json_object_get_wrapping_value(result);
}
JSON_Value *struct_sticker_item(sticker_item_t *sticker_item) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    json_object_set_string(result, "id", sticker_item->id);
    json_object_set_string(result, "name", sticker_item->name);
    json_object_set_number(result, "format_type", sticker_item->format_type);

    return json_object_get_wrapping_value(result);
}
JSON_Value *struct_sticker(sticker_t *sticker) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    json_object_set_string(result, "id", sticker->id);
    json_object_set_string(result, "pack_id", sticker->pack_id);
    json_object_set_string(result, "name", sticker->name);
    json_object_set_string(result, "description", sticker->description);
    json_object_set_string(result, "tags", sticker->tags);
    json_object_set_string(result, "asset", sticker->asset);
    json_object_set_number(result, "type", sticker->type);
    json_object_set_number(result, "format_type", sticker->format_type);
    json_object_set_boolean(result, "available", sticker->available);
    json_object_set_string(result, "guild_id", sticker->guild_id);
    json_object_set_value(result, "user", struct_user(sticker->user));
    json_object_set_number(result, "sort_value", sticker->sort_value);

    return json_object_get_wrapping_value(result);
}
