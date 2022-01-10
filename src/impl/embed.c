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

#include "embed.h"

embed_t *parse_embed(JSON_Value *embed_value) {
    JSON_Object *embed = json_object(embed_value);
    embed_t *result = yadl_malloc(sizeof(embed_t), true);
    *result = (embed_t) {(char *) json_object_get_string(embed, "title"),
                         (char *) json_object_get_string(embed, "type"),
                         (char *) json_object_get_string(embed, "description"),
                         (char *) json_object_get_string(embed, "url"),
                         (char *) json_object_get_string(embed, "timestamp"),
                         (int) json_object_get_number(embed, "color"),
                         (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(embed, "footer"))),
                         (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(embed, "image"))),
                         (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(embed, "thumbnail"))),
                         (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(embed, "video"))),
                         (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(embed, "provider"))),
                         (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(embed, "author"))),
                         (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(embed, "fields")))
    };

    return result;
}

embed_thumbnail_t *parse_embed_thumbnail(JSON_Value *embed_thumbnail_value) {
    JSON_Object *embed_thumbnail = json_object(embed_thumbnail_value);
    embed_thumbnail_t *result = yadl_malloc(sizeof(embed_thumbnail_t), true);
    *result = (embed_thumbnail_t) {(char *) json_object_get_string(embed_thumbnail, "url"),
                                   (char *) json_object_get_string(embed_thumbnail, "proxy_url"),
                                   (int) json_object_get_number(embed_thumbnail, "height"),
                                   (int) json_object_get_number(embed_thumbnail, "width")
    };

    return result;
}

embed_video_t *parse_embed_video(JSON_Value *embed_video_value) {
    JSON_Object *embed_video = json_object(embed_video_value);
    embed_video_t *result = yadl_malloc(sizeof(embed_video_t), true);
    *result = (embed_video_t) {(char *) json_object_get_string(embed_video, "url"),
                               (char *) json_object_get_string(embed_video, "proxy_url"),
                               (int) json_object_get_number(embed_video, "height"),
                               (int) json_object_get_number(embed_video, "width")
    };

    return result;
}

embed_image_t *parse_embed_image(JSON_Value *embed_image_value) {
    JSON_Object *embed_image = json_object(embed_image_value);
    embed_image_t *result = yadl_malloc(sizeof(embed_image_t), true);
    *result = (embed_image_t) {(char *) json_object_get_string(embed_image, "url"),
                               (char *) json_object_get_string(embed_image, "proxy_url"),
                               (int) json_object_get_number(embed_image, "height"),
                               (int) json_object_get_number(embed_image, "width")
    };

    return result;
}

embed_provider_t *parse_embed_provider(JSON_Value *embed_provider_value) {
    JSON_Object *embed_provider = json_object(embed_provider_value);
    embed_provider_t *result = yadl_malloc(sizeof(embed_provider_t), true);
    *result = (embed_provider_t) {(char *) json_object_get_string(embed_provider, "name"),
                                  (char *) json_object_get_string(embed_provider, "url")
    };

    return result;
}

embed_author_t *parse_embed_author(JSON_Value *embed_author_value) {
    JSON_Object *embed_author = json_object(embed_author_value);
    embed_author_t *result = yadl_malloc(sizeof(embed_author_t), true);
    *result = (embed_author_t) {(char *) json_object_get_string(embed_author, "name"),
                                (char *) json_object_get_string(embed_author, "url"),
                                (char *) json_object_get_string(embed_author, "icon_url"),
                                (char *) json_object_get_string(embed_author, "proxy_icon_url")
    };

    return result;
}

embed_footer_t *parse_embed_footer(JSON_Value *embed_footer_value) {
    JSON_Object *embed_footer = json_object(embed_footer_value);
    embed_footer_t *result = yadl_malloc(sizeof(embed_footer_t), true);
    *result = (embed_footer_t) {(char *) json_object_get_string(embed_footer, "text"),
                                (char *) json_object_get_string(embed_footer, "icon_url"),
                                (char *) json_object_get_string(embed_footer, "proxy_icon_url")
    };

    return result;
}

embed_field_t *parse_embed_field(JSON_Value *embed_field_value) {
    JSON_Object *embed_field = json_object(embed_field_value);
    embed_field_t *result = yadl_malloc(sizeof(embed_field_t), true);
    *result = (embed_field_t) {(char *) json_object_get_string(embed_field, "name"),
                               (char *) json_object_get_string(embed_field, "value"),
                               yadl_json_boolean_null_check(json_object_get_boolean(embed_field, "inline"))
    };

    return result;
}
