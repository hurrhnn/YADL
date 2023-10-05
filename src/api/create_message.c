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

#include <yadl/api/create_message.h>

void yadl_create_message(yadl_context_t *context, const char *channel_id, const char *content, bool is_tts,
                         yadl_object_array_t *embeds,
                         allowed_mentions_t *allowed_mentions, message_reference_t *message_reference,
                         yadl_object_array_t *attachments, yadl_object_array_t *files) {

    char *create_message = yadl_malloc(YADL_MIDIUM_SIZE),
            *headers = yadl_malloc(YADL_MIDIUM_SIZE), **payload = yadl_malloc(sizeof(void *));
    snprintf(create_message, YADL_MIDIUM_SIZE,
             yadl_strcat(context->info.API_URL, YADL_CREATE_MESSAGE_PATH), channel_id);
    snprintf(headers, YADL_MIDIUM_SIZE, context->info.AUTHORIZATION_HEADER, context->info.TOKEN);

    JSON_Object *json_payload = yadl_json_object_builder(NULL);
    if (content != NULL)
        json_object_dotset_string(json_payload, "content", content);

    json_object_dotset_boolean(json_payload, "tts", is_tts);

    if (embeds != NULL) {
        JSON_Array *json_embeds = yadl_json_array_builder(NULL);
        for (int i = 0; i < embeds->size; i++)
            json_array_append_value(json_embeds, struct_embed((embed_t *) embeds->array[i]));
        json_object_dotset_value(json_payload, "embeds", json_array_get_wrapping_value(json_embeds));
    }

    if(allowed_mentions != NULL)
        json_object_dotset_value(json_payload, "allowed_mentions", struct_allowed_mentions(allowed_mentions));

    if (message_reference != NULL)
        json_object_dotset_value(json_payload, "message_reference", struct_message_reference(message_reference));

    if (attachments != NULL) {
        *payload = yadl_malloc((YADL_LARGE_SIZE * 2) + YADL_CREATE_MESSAGE_LIMIT_ATTACHMENT_SIZE * attachments->size);
        headers = yadl_strcat(headers, "\nContent-Type: multipart/form-data; boundary=boundary");

        JSON_Array *json_attachments = yadl_json_array_builder(NULL);
        for (int i = 0; i < attachments->size; i++) {
            char *id = yadl_malloc(YADL_SMALL_SIZE);
            sprintf(id, "%d", i);

            attachment_t *attachment = (attachment_t*) attachments->array[i];
            attachment->id = id;
            json_array_append_value(json_attachments, struct_attachment(attachment));
        }
        json_object_dotset_value(json_payload, "attachments", json_array_get_wrapping_value(json_attachments));

        size_t current_length = 0;
        current_length += sprintf(*payload + current_length, "--boundary\n"
                                                             "Content-Disposition: form-data; name=\"payload_json\"\n"
                                                             "Content-Type: application/json\n\n");

        current_length += sprintf(*payload + current_length, "%s\n",
                                  json_serialize_to_string_pretty(json_object_get_wrapping_value(json_payload)));

        for (int i = 0; i < attachments->size; i++) {
            current_length += sprintf(*payload + current_length, "\n--boundary\n"
                                                                 "Content-Disposition: form-data; name=\"files[%d]\"; filename=\"%s\"\n"
                                                                 "Content-Type: application/octet-stream\n\n", i,
                                      ((attachment_t *) attachments->array[i])->filename);

            memcpy(*payload + current_length, files->array[i], ((attachment_t *) attachments->array[i])->size);
            current_length += ((attachment_t *) attachments->array[i])->size;
        }

        current_length += sprintf(*payload + current_length, "\n--boundary--");
        http_request("POST", create_message, headers, NULL, context->info.APPLICATION, payload, current_length);
    } else {
        *payload = json_serialize_to_string(json_object_get_wrapping_value(json_payload));
        http_request("POST", create_message, headers, NULL,
                     context->info.APPLICATION, payload, strlen(*payload));
    }
}
