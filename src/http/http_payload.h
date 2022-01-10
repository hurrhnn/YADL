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

#ifndef YADL_HTTP_PAYLOAD_H
#define YADL_HTTP_PAYLOAD_H

#include "libwebsockets.h"
#include <string.h>
#include <stdbool.h>

struct http_payload {
    struct lws *client_wsi;
    bool status;

    char *address;
    char *path;
    const char *method;
    char *user_agent;

    bool data_ready;
    u_int32_t *response_code;
    size_t header_len;
    size_t cookie_len;
    size_t request_body_len;
    size_t response_body_len;
    size_t current_response_len;

    char *header;
    char *cookie;
    char **request_body;
    char **response_body;
};

#endif
