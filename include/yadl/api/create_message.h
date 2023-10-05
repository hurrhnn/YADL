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

#ifndef YADL_CREATE_MESSAGE_H
#define YADL_CREATE_MESSAGE_H

#include "yadl/utils/utils.h"
#include "yadl/http/http_request.h"
#include "yadl/impl/impl.h"
#include "yadl.h"

#define YADL_CREATE_MESSAGE_PATH "/channels/%s/messages"
#define YADL_CREATE_MESSAGE_LIMIT_ATTACHMENT_SIZE 8388608

void yadl_create_message(yadl_context_t *context, const char *channel_id, const char *content, bool is_tts, yadl_object_array_t *embeds,
                         allowed_mentions_t *allowed_mentions, message_reference_t *message_reference,
                         yadl_object_array_t *attachments, yadl_object_array_t *files);

#endif //YADL_CREATE_MESSAGE_H
