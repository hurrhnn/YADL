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

#include "message.h"
#include "impl.h"

message_t *parse_referenced_message(JSON_Value *parse_referenced_message) {
    JSON_Object *referenced_message = json_object(parse_referenced_message);
    message_t *result = yadl_malloc(sizeof(message_t));

    *result = (message_t) {(char *) json_object_get_string(referenced_message, "id"),
                           (char *) json_object_get_string(referenced_message, "channel_id"),
                           (char *) json_object_get_string(referenced_message, "guild_id"),
                           parse_user(json_object_get_wrapping_value(json_object_get_object(referenced_message, "author"))),
                           parse_guild_member(json_object_get_wrapping_value(json_object_get_object(referenced_message, "member"))),
                           (char *) json_object_get_string(referenced_message, "content"),
                           (char *) json_object_get_string(referenced_message, "timestamp"),
                           (char *) json_object_get_string(referenced_message, "edited_timestamp"),
                           yadl_json_boolean_null_check(json_object_get_boolean(referenced_message, "tts")),
                           yadl_json_boolean_null_check(json_object_get_boolean(referenced_message, "mention_everyone")),
                           yadl_object_array_parse(YADL_OBJECT_USER, json_object_get_array(referenced_message, "mentions")),
                           (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(referenced_message, "mention_roles"))),
                           yadl_object_array_parse(YADL_OBJECT_CHANNEL_MENTION, json_object_get_array(referenced_message, "mention_channels")),
                           yadl_object_array_parse(YADL_OBJECT_ATTACHMENT, json_object_get_array(referenced_message, "attachments")),
                           yadl_object_array_parse(YADL_OBJECT_EMBED, json_object_get_array(referenced_message, "embeds")),
                           yadl_object_array_parse(YADL_OBJECT_REACTION, json_object_get_array(referenced_message, "reactions")),
                           (char *) json_object_get_string(referenced_message, "nonce"),
                           yadl_json_boolean_null_check(json_object_get_boolean(referenced_message, "pinned")),
                           (char *) json_object_get_string(referenced_message, "webhook_id"),
                           (int) json_object_get_number(referenced_message, "type"),
                           (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(referenced_message, "activity"))),
                           parse_application(json_object_get_wrapping_value(json_object_get_object(referenced_message, "application"))),
                           (char *) json_object_get_string(referenced_message, "application_id"),
                           parse_message_reference(json_object_get_wrapping_value(json_object_get_object(referenced_message, "message_reference"))),
                           (int) json_object_get_number(referenced_message, "flags"),
                           NULL,
                           parse_integration(json_object_get_wrapping_value(json_object_get_object(referenced_message, "interaction"))),
                           parse_channel(json_object_get_wrapping_value(json_object_get_object(referenced_message, "thread"))),
                           (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(referenced_message, "components"))),
                           yadl_object_array_parse(YADL_OBJECT_STICKER_ITEM, json_object_get_array(referenced_message, "sticker_items")),
                           yadl_object_array_parse(YADL_OBJECT_STICKER, json_object_get_array(referenced_message, "stickers"))
    };

    return result;
}

message_t *parse_message(JSON_Value *message_value) {
    JSON_Object *message = json_object(message_value);
    message_t *result = yadl_malloc(sizeof(message_t));

    *result = (message_t) {(char *) json_object_get_string(message, "id"),
                           (char *) json_object_get_string(message, "channel_id"),
                           (char *) json_object_get_string(message, "guild_id"),
                           parse_user(json_object_get_wrapping_value(json_object_get_object(message, "author"))),
                           parse_guild_member(json_object_get_wrapping_value(json_object_get_object(message, "member"))),
                           (char *) json_object_get_string(message, "content"),
                           (char *) json_object_get_string(message, "timestamp"),
                           (char *) json_object_get_string(message, "edited_timestamp"),
                           yadl_json_boolean_null_check(json_object_get_boolean(message, "tts")),
                           yadl_json_boolean_null_check(json_object_get_boolean(message, "mention_everyone")),
                           yadl_object_array_parse(YADL_OBJECT_USER, json_object_get_array(message, "mentions")),
                           (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(message, "mention_roles"))),
                           yadl_object_array_parse(YADL_OBJECT_CHANNEL_MENTION, json_object_get_array(message, "mention_channels")),
                           yadl_object_array_parse(YADL_OBJECT_ATTACHMENT, json_object_get_array(message, "attachments")),
                           yadl_object_array_parse(YADL_OBJECT_EMBED, json_object_get_array(message, "embeds")),
                           yadl_object_array_parse(YADL_OBJECT_REACTION, json_object_get_array(message, "reactions")),
                           (char *) json_object_get_string(message, "nonce"),
                           yadl_json_boolean_null_check(json_object_get_boolean(message, "pinned")),
                           (char *) json_object_get_string(message, "webhook_id"),
                           (int) json_object_get_number(message, "type"),
                           (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(message, "activity"))),
                           parse_application(json_object_get_wrapping_value(json_object_get_object(message, "application"))),
                           (char *) json_object_get_string(message, "application_id"),
                           parse_message_reference(json_object_get_wrapping_value(json_object_get_object(message, "message_reference"))),
                           (int) json_object_get_number(message, "flags"),
                           (message_t *) parse_referenced_message(json_object_get_wrapping_value(json_object_get_object(message, "referenced_message"))),
                           parse_integration(json_object_get_wrapping_value(json_object_get_object(message, "interaction"))),
                           parse_channel(json_object_get_wrapping_value(json_object_get_object(message, "thread"))),
                           (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(message, "components"))),
                           yadl_object_array_parse(YADL_OBJECT_STICKER_ITEM, json_object_get_array(message, "sticker_items")),
                           yadl_object_array_parse(YADL_OBJECT_STICKER, json_object_get_array(message, "stickers"))
    };

    return result;
}

message_activity_t *parse_message_activity(JSON_Value *message_activity_value) {
    JSON_Object *message_activity = json_object(message_activity_value);
    message_activity_t *result = yadl_malloc(sizeof(message_activity_t));
    *result = (message_activity_t) {(int) json_object_get_number(message_activity, "type"),
                                    (char *) json_object_get_string(message_activity, "party_id")
    };

    return result;
}

message_reference_t *parse_message_reference(JSON_Value *message_reference_value) {
    JSON_Object *message_reference = json_object(message_reference_value);
    message_reference_t *result = yadl_malloc(sizeof(message_reference_t));
    *result = (message_reference_t) {(char *) json_object_get_string(message_reference, "message_id"),
                                     (char *) json_object_get_string(message_reference, "channel_id"),
                                     (char *) json_object_get_string(message_reference, "guild_id"),
                                     yadl_json_boolean_null_check(json_object_get_boolean(message_reference, "fail_if_not_exists"))
    };

    return result;
}

followed_channel_t *parse_followed_channel(JSON_Value *followed_channel_value) {
    JSON_Object *followed_channel = json_object(followed_channel_value);
    followed_channel_t *result = yadl_malloc(sizeof(followed_channel_t));
    *result = (followed_channel_t) {(char *) json_object_get_string(followed_channel, "channel_id"),
                                    (char *) json_object_get_string(followed_channel, "webhook_id")
    };

    return result;
}

JSON_Value *struct_followed_channel(followed_channel_t *followed_channel) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    json_object_set_string(result, "channel_id", followed_channel->channel_id);
    json_object_set_string(result, "webhook_id", followed_channel->webhook_id);

    return json_object_get_wrapping_value(result);
}
JSON_Value *struct_message_reference(message_reference_t *message_reference) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    json_object_set_string(result, "message_id", message_reference->message_id);
    json_object_set_string(result, "channel_id", message_reference->channel_id);
    json_object_set_string(result, "guild_id", message_reference->guild_id);
    json_object_set_boolean(result, "fail_if_not_exists", message_reference->fail_if_not_exists);

    return json_object_get_wrapping_value(result);
}
JSON_Value *struct_message_activity(message_activity_t *message_activity) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    json_object_set_number(result, "type", message_activity->type);
    json_object_set_string(result, "party_id", message_activity->party_id);

    return json_object_get_wrapping_value(result);
}

JSON_Value *struct_referenced_message(message_t *referenced_message) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    json_object_set_string(result, "id", referenced_message->id);
    json_object_set_string(result, "channel_id", referenced_message->channel_id);
    json_object_set_string(result, "guild_id", referenced_message->guild_id);
    json_object_set_value(result, "author", struct_user(referenced_message->author));
    json_object_set_value(result, "member", struct_guild_member(referenced_message->member));
    json_object_set_string(result, "content", referenced_message->content);
    json_object_set_string(result, "timestamp", referenced_message->timestamp);
    json_object_set_string(result, "edited_timestamp", referenced_message->edited_timestamp);
    json_object_set_boolean(result, "tts", referenced_message->tts);
    json_object_set_boolean(result, "mention_everyone", referenced_message->mention_everyone);

    JSON_Array *mentions = yadl_json_array_builder(NULL);
    for (int i=0; i<referenced_message->mentions->size; i++)
        json_array_append_value(mentions, struct_user((user_t *)referenced_message->mentions->array[i]));

    json_object_set_string(result, "mention_roles", referenced_message->mention_roles);

    JSON_Array *mention_channels = yadl_json_array_builder(NULL);
    for (int i=0; i<referenced_message->mention_channels->size; i++)
        json_array_append_value(mention_channels, struct_channel_mention((channel_mention_t *)referenced_message->mention_channels->array[i]));


    JSON_Array *attachments = yadl_json_array_builder(NULL);
    for (int i=0; i<referenced_message->attachments->size; i++)
        json_array_append_value(attachments, struct_attachment((attachment_t *)referenced_message->attachments->array[i]));


    JSON_Array *embeds = yadl_json_array_builder(NULL);
    for (int i=0; i<referenced_message->embeds->size; i++)
        json_array_append_value(embeds, struct_embed((embed_t *)referenced_message->embeds->array[i]));


    JSON_Array *reactions = yadl_json_array_builder(NULL);
    for (int i=0; i<referenced_message->reactions->size; i++)
        json_array_append_value(reactions, struct_reaction((reaction_t *)referenced_message->reactions->array[i]));

    json_object_set_string(result, "nonce", referenced_message->nonce);
    json_object_set_boolean(result, "pinned", referenced_message->pinned);
    json_object_set_string(result, "webhook_id", referenced_message->webhook_id);
    json_object_set_number(result, "type", referenced_message->type);
    json_object_set_string(result, "activity", referenced_message->activity);
    json_object_set_value(result, "application", struct_application(referenced_message->application));
    json_object_set_string(result, "application_id", referenced_message->application_id);
    json_object_set_value(result, "message_reference", struct_message_reference(referenced_message->message_reference));
    json_object_set_number(result, "flags", referenced_message->flags);
    json_object_set_value(result, "interaction", struct_integration(referenced_message->interaction));
    json_object_set_value(result, "thread", struct_channel(referenced_message->thread));
    json_object_set_string(result, "components", referenced_message->components);

    JSON_Array *sticker_items = yadl_json_array_builder(NULL);
    for (int i=0; i<referenced_message->sticker_items->size; i++)
        json_array_append_value(sticker_items, struct_sticker_item((sticker_item_t *)referenced_message->sticker_items->array[i]));


    JSON_Array *stickers = yadl_json_array_builder(NULL);
    for (int i=0; i<referenced_message->stickers->size; i++)
        json_array_append_value(stickers, struct_sticker((sticker_t *)referenced_message->stickers->array[i]));


    return json_object_get_wrapping_value(result);
}

JSON_Value *struct_message(message_t *message) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    json_object_set_string(result, "id", message->id);
    json_object_set_string(result, "channel_id", message->channel_id);
    json_object_set_string(result, "guild_id", message->guild_id);
    json_object_set_value(result, "author", struct_user(message->author));
    json_object_set_value(result, "member", struct_guild_member(message->member));
    json_object_set_string(result, "content", message->content);
    json_object_set_string(result, "timestamp", message->timestamp);
    json_object_set_string(result, "edited_timestamp", message->edited_timestamp);
    json_object_set_boolean(result, "tts", message->tts);
    json_object_set_boolean(result, "mention_everyone", message->mention_everyone);

    JSON_Array *mentions = yadl_json_array_builder(NULL);
    for (int i=0; i<message->mentions->size; i++)
        json_array_append_value(mentions, struct_user((user_t *)message->mentions->array[i]));

    json_object_set_string(result, "mention_roles", message->mention_roles);

    JSON_Array *mention_channels = yadl_json_array_builder(NULL);
    for (int i=0; i<message->mention_channels->size; i++)
        json_array_append_value(mention_channels, struct_channel_mention((channel_mention_t *)message->mention_channels->array[i]));


    JSON_Array *attachments = yadl_json_array_builder(NULL);
    for (int i=0; i<message->attachments->size; i++)
        json_array_append_value(attachments, struct_attachment((attachment_t *)message->attachments->array[i]));


    JSON_Array *embeds = yadl_json_array_builder(NULL);
    for (int i=0; i<message->embeds->size; i++)
        json_array_append_value(embeds, struct_embed((embed_t *)message->embeds->array[i]));


    JSON_Array *reactions = yadl_json_array_builder(NULL);
    for (int i=0; i<message->reactions->size; i++)
        json_array_append_value(reactions, struct_reaction((reaction_t *)message->reactions->array[i]));

    json_object_set_string(result, "nonce", message->nonce);
    json_object_set_boolean(result, "pinned", message->pinned);
    json_object_set_string(result, "webhook_id", message->webhook_id);
    json_object_set_number(result, "type", message->type);
    json_object_set_string(result, "activity", message->activity);
    json_object_set_value(result, "application", struct_application(message->application));
    json_object_set_string(result, "application_id", message->application_id);
    json_object_set_value(result, "message_reference", struct_message_reference(message->message_reference));
    json_object_set_number(result, "flags", message->flags);
    json_object_set_value(result, "referenced_message", struct_referenced_message(message->referenced_message));
    json_object_set_value(result, "interaction", struct_integration(message->interaction));
    json_object_set_value(result, "thread", struct_channel(message->thread));
    json_object_set_string(result, "components", message->components);

    JSON_Array *sticker_items = yadl_json_array_builder(NULL);
    for (int i=0; i<message->sticker_items->size; i++)
        json_array_append_value(sticker_items, struct_sticker_item((sticker_item_t *)message->sticker_items->array[i]));


    JSON_Array *stickers = yadl_json_array_builder(NULL);
    for (int i=0; i<message->stickers->size; i++)
        json_array_append_value(stickers, struct_sticker((sticker_t *)message->stickers->array[i]));


    return json_object_get_wrapping_value(result);
}
