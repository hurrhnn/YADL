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

#ifndef YADL_HTTP_REQUEST_H
#define YADL_HTTP_REQUEST_H

#include <libwebsockets.h>
#include "http_payload.h"
#include "http_result.h"
#include "yadl/gc/pthread.h"
#include "gc/gc.h"

http_result_t *
http_request(const char *method, const char *URL, char *header, char *cookie, const char *user_agent, char **request_body, size_t request_body_size);

#endif
