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

#include <yadl/impl/embed.h>
#include <yadl/impl/impl.h>

embed_t *parse_embed(JSON_Value *embed_value) {
    JSON_Object *embed = json_object(embed_value);
    embed_t *result = yadl_malloc(sizeof(embed_t));
    *result = (embed_t) {(char *) json_object_get_string(embed, "title"),
                         (char *) json_object_get_string(embed, "type"),
                         (char *) json_object_get_string(embed, "description"),
                         (char *) json_object_get_string(embed, "url"),
                         (char *) json_object_get_string(embed, "timestamp"),
                         (int) json_object_get_number(embed, "color"),
                         parse_embed_footer(json_object_get_wrapping_value(json_object_get_object(embed, "footer"))),
                         parse_embed_image(json_object_get_wrapping_value(json_object_get_object(embed, "image"))),
                          parse_embed_thumbnail(json_object_get_wrapping_value(json_object_get_object(embed, "thumbnail"))),
                         parse_embed_video(json_object_get_wrapping_value(json_object_get_object(embed, "video"))),
                         parse_embed_provider(json_object_get_wrapping_value(json_object_get_object(embed, "provider"))),
                         parse_embed_author(json_object_get_wrapping_value(json_object_get_object(embed, "author"))),
                         yadl_object_array_parse(YADL_OBJECT_EMBED_FIELD,(json_object_get_array(embed, "fields")))
    };

    return result;
}

embed_thumbnail_t *parse_embed_thumbnail(JSON_Value *embed_thumbnail_value) {
    JSON_Object *embed_thumbnail = json_object(embed_thumbnail_value);
    embed_thumbnail_t *result = yadl_malloc(sizeof(embed_thumbnail_t));
    *result = (embed_thumbnail_t) {(char *) json_object_get_string(embed_thumbnail, "url"),
                                   (char *) json_object_get_string(embed_thumbnail, "proxy_url"),
                                   (int) json_object_get_number(embed_thumbnail, "height"),
                                   (int) json_object_get_number(embed_thumbnail, "width")
    };

    return result;
}

embed_video_t *parse_embed_video(JSON_Value *embed_video_value) {
    JSON_Object *embed_video = json_object(embed_video_value);
    embed_video_t *result = yadl_malloc(sizeof(embed_video_t));
    *result = (embed_video_t) {(char *) json_object_get_string(embed_video, "url"),
                               (char *) json_object_get_string(embed_video, "proxy_url"),
                               (int) json_object_get_number(embed_video, "height"),
                               (int) json_object_get_number(embed_video, "width")
    };

    return result;
}

embed_image_t *parse_embed_image(JSON_Value *embed_image_value) {
    JSON_Object *embed_image = json_object(embed_image_value);
    embed_image_t *result = yadl_malloc(sizeof(embed_image_t));
    *result = (embed_image_t) {(char *) json_object_get_string(embed_image, "url"),
                               (char *) json_object_get_string(embed_image, "proxy_url"),
                               (int) json_object_get_number(embed_image, "height"),
                               (int) json_object_get_number(embed_image, "width")
    };

    return result;
}

embed_provider_t *parse_embed_provider(JSON_Value *embed_provider_value) {
    JSON_Object *embed_provider = json_object(embed_provider_value);
    embed_provider_t *result = yadl_malloc(sizeof(embed_provider_t));
    *result = (embed_provider_t) {(char *) json_object_get_string(embed_provider, "name"),
                                  (char *) json_object_get_string(embed_provider, "url")
    };

    return result;
}

embed_author_t *parse_embed_author(JSON_Value *embed_author_value) {
    JSON_Object *embed_author = json_object(embed_author_value);
    embed_author_t *result = yadl_malloc(sizeof(embed_author_t));
    *result = (embed_author_t) {(char *) json_object_get_string(embed_author, "name"),
                                (char *) json_object_get_string(embed_author, "url"),
                                (char *) json_object_get_string(embed_author, "icon_url"),
                                (char *) json_object_get_string(embed_author, "proxy_icon_url")
    };

    return result;
}

embed_footer_t *parse_embed_footer(JSON_Value *embed_footer_value) {
    JSON_Object *embed_footer = json_object(embed_footer_value);
    embed_footer_t *result = yadl_malloc(sizeof(embed_footer_t));
    *result = (embed_footer_t) {(char *) json_object_get_string(embed_footer, "text"),
                                (char *) json_object_get_string(embed_footer, "icon_url"),
                                (char *) json_object_get_string(embed_footer, "proxy_icon_url")
    };

    return result;
}

embed_field_t *parse_embed_field(JSON_Value *embed_field_value) {
    JSON_Object *embed_field = json_object(embed_field_value);
    embed_field_t *result = yadl_malloc(sizeof(embed_field_t));
    *result = (embed_field_t) {(char *) json_object_get_string(embed_field, "name"),
                               (char *) json_object_get_string(embed_field, "value"),
                               yadl_json_boolean_null_check(json_object_get_boolean(embed_field, "inline"))
    };

    return result;
}

JSON_Value *struct_embed_field(embed_field_t *embed_field) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    if(embed_field != NULL) {
        json_object_set_string(result, "name", embed_field->name);
        json_object_set_string(result, "value", embed_field->value);
        json_object_set_boolean(result, "inline", embed_field->inline_);
    }

    return json_object_get_wrapping_value(result);
}
JSON_Value *struct_embed_footer(embed_footer_t *embed_footer) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    if(embed_footer != NULL) {
        json_object_set_string(result, "text", embed_footer->text);
        json_object_set_string(result, "icon_url", embed_footer->icon_url);
        json_object_set_string(result, "proxy_icon_url", embed_footer->proxy_icon_url);
    }

    return json_object_get_wrapping_value(result);
}
JSON_Value *struct_embed_author(embed_author_t *embed_author) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    if(embed_author != NULL) {
        json_object_set_string(result, "name", embed_author->name);
        json_object_set_string(result, "url", embed_author->url);
        json_object_set_string(result, "icon_url", embed_author->icon_url);
        json_object_set_string(result, "proxy_icon_url", embed_author->proxy_icon_url);
    }

    return json_object_get_wrapping_value(result);
}
JSON_Value *struct_embed_provider(embed_provider_t *embed_provider) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    if(embed_provider != NULL) {
        json_object_set_string(result, "name", embed_provider->name);
        json_object_set_string(result, "url", embed_provider->url);
    }

    return json_object_get_wrapping_value(result);
}
JSON_Value *struct_embed_image(embed_image_t *embed_image) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    if(embed_image != NULL) {
        json_object_set_string(result, "url", embed_image->url);
        json_object_set_string(result, "proxy_url", embed_image->proxy_url);
        json_object_set_number(result, "height", embed_image->height);
        json_object_set_number(result, "width", embed_image->width);
    }

    return json_object_get_wrapping_value(result);
}
JSON_Value *struct_embed_video(embed_video_t *embed_video) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    if(embed_video != NULL) {
        json_object_set_string(result, "url", embed_video->url);
        json_object_set_string(result, "proxy_url", embed_video->proxy_url);
        json_object_set_number(result, "height", embed_video->height);
        json_object_set_number(result, "width", embed_video->width);
    }

    return json_object_get_wrapping_value(result);
}
JSON_Value *struct_embed_thumbnail(embed_thumbnail_t *embed_thumbnail) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    if(embed_thumbnail != NULL) {
        json_object_set_string(result, "url", embed_thumbnail->url);
        json_object_set_string(result, "proxy_url", embed_thumbnail->proxy_url);
        json_object_set_number(result, "height", embed_thumbnail->height);
        json_object_set_number(result, "width", embed_thumbnail->width);
    }

    return json_object_get_wrapping_value(result);
}
JSON_Value *struct_embed(embed_t *embed) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    if(embed != NULL) {
        json_object_set_string(result, "title", embed->title);
        json_object_set_string(result, "type", embed->type);
        json_object_set_string(result, "description", embed->description);
        json_object_set_string(result, "url", embed->url);
        json_object_set_string(result, "timestamp", embed->timestamp);
        json_object_set_number(result, "color", embed->color);
        json_object_set_value(result, "footer", struct_embed_footer(embed->footer));
        json_object_set_value(result, "image", struct_embed_image(embed->image));
        json_object_set_value(result, "thumbnail", struct_embed_thumbnail(embed->thumbnail));
        json_object_set_value(result, "video", struct_embed_video(embed->video));
        json_object_set_value(result, "provider", struct_embed_provider(embed->provider));
        json_object_set_value(result, "author", struct_embed_author(embed->author));

        JSON_Array *fields = yadl_json_array_builder(NULL);
        if(embed->fields != NULL) {
            for (int i=0; i<embed->fields->size; i++)
                json_array_append_value(fields, struct_embed_field((embed_field_t *)embed->fields->array[i]));
        }
        json_object_set_value(result, "fields", json_array_get_wrapping_value(fields));
    }

    return json_object_get_wrapping_value(result);
}
