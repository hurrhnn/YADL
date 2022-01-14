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

#ifndef YADL_EMBED_H
#define YADL_EMBED_H

#include <stdbool.h>
#include "../utils/utils.h"
#include "parson.h"
#include "../json/json.h"

typedef struct yadl_object_array yadl_object_array_t;

typedef struct __attribute__((__packed__)) {
    char *url;
    char *proxy_url;
    int height;
    int width;

} embed_thumbnail_t;

typedef struct __attribute__((__packed__)) {
    char *url;
    char *proxy_url;
    int height;
    int width;

} embed_video_t;

typedef struct __attribute__((__packed__)) {
    char *url;
    char *proxy_url;
    int height;
    int width;

} embed_image_t;

typedef struct __attribute__((__packed__)) {
    char *name;
    char *url;

} embed_provider_t;

typedef struct __attribute__((__packed__)) {
    char *name;
    char *url;
    char *icon_url;
    char *proxy_icon_url;

} embed_author_t;

typedef struct __attribute__((__packed__)) {
    char *text;
    char *icon_url;
    char *proxy_icon_url;

} embed_footer_t;

typedef struct __attribute__((__packed__)) {
    char *name;
    char *value;
    bool inline_; // fuck

} embed_field_t;

typedef struct __attribute__((__packed__)) {
    char *title;
    char *type;
    char *description;
    char *url;
    char *timestamp;
    int color;
    embed_footer_t *footer;
    /* embed footer object */
    embed_image_t *image;
    /* embed image object */
    embed_thumbnail_t *thumbnail;
    /* embed thumbnail object */
    embed_video_t *video;
    /* embed video object */
    embed_provider_t *provider;
    /* embed provider object */
    embed_author_t *author;
    /* embed author object */
    yadl_object_array_t *fields;
    /* array of embed field objects */

} embed_t;

embed_t *parse_embed(JSON_Value *embed_value);

embed_thumbnail_t *parse_embed_thumbnail(JSON_Value *embed_thumbnail_value);

embed_video_t *parse_embed_video(JSON_Value *embed_video_value);

embed_image_t *parse_embed_image(JSON_Value *embed_image_value);

embed_provider_t *parse_embed_provider(JSON_Value *embed_provider_value);

embed_author_t *parse_embed_author(JSON_Value *embed_author_value);

embed_footer_t *parse_embed_footer(JSON_Value *embed_footer_value);

embed_field_t *parse_embed_field(JSON_Value *embed_field_value);

JSON_Value *struct_embed_field(embed_field_t *embed_field);

JSON_Value *struct_embed_footer(embed_footer_t *embed_footer);

JSON_Value *struct_embed_author(embed_author_t *embed_author);

JSON_Value *struct_embed_provider(embed_provider_t *embed_provider);

JSON_Value *struct_embed_image(embed_image_t *embed_image);

JSON_Value *struct_embed_video(embed_video_t *embed_video);

JSON_Value *struct_embed_thumbnail(embed_thumbnail_t *embed_thumbnail);

JSON_Value *struct_embed(embed_t *embed);

#endif //YADL_EMBED_H
