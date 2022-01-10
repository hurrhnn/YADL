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

typedef struct yadl_embed {
    char *title;
    char *type;
    char *description;
    char *url;
    char *timestamp;
    int color;
    char *footer;
    /* embed footer object */
    char *image;
    /* embed image object */
    char *thumbnail;
    /* embed thumbnail object */
    char *video;
    /* embed video object */
    char *provider;
    /* embed provider object */
    char *author;
    /* embed author object */
    char *fields;
    /* array of embed field objects */

} embed_t;

typedef struct yadl_embed_thumbnail {
    char *url;
    char *proxy_url;
    int height;
    int width;

} embed_thumbnail_t;

typedef struct yadl_embed_video {
    char *url;
    char *proxy_url;
    int height;
    int width;

} embed_video_t;

typedef struct yadl_embed_image {
    char *url;
    char *proxy_url;
    int height;
    int width;

} embed_image_t;

typedef struct yadl_embed_provider {
    char *name;
    char *url;

} embed_provider_t;

typedef struct yadl_embed_author {
    char *name;
    char *url;
    char *icon_url;
    char *proxy_icon_url;

} embed_author_t;

typedef struct yadl_embed_footer {
    char *text;
    char *icon_url;
    char *proxy_icon_url;

} embed_footer_t;

typedef struct yadl_embed_field {
    char *name;
    char *value;
    bool inline_; // fuck

} embed_field_t;

embed_t *parse_embed(JSON_Value *embed_value);

embed_thumbnail_t *parse_embed_thumbnail(JSON_Value *embed_thumbnail_value);

embed_video_t *parse_embed_video(JSON_Value *embed_video_value);

embed_image_t *parse_embed_image(JSON_Value *embed_image_value);

embed_provider_t *parse_embed_provider(JSON_Value *embed_provider_value);

embed_author_t *parse_embed_author(JSON_Value *embed_author_value);

embed_footer_t *parse_embed_footer(JSON_Value *embed_footer_value);

embed_field_t *parse_embed_field(JSON_Value *embed_field_value);

#endif //YADL_EMBED_H
