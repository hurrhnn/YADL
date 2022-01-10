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

#include "get_current_user.h"

self_user_t *yadl_get_self_user(yadl_context_t *context) {
    char *get_self_user = yadl_malloc(YADL_MIDIUM_SIZE),
            *authorization_header = yadl_malloc(YADL_MIDIUM_SIZE);
    snprintf(get_self_user, YADL_MIDIUM_SIZE, "%s", yadl_strcat(context->info.API_URL, YADL_GET_CURRENT_USER_PATH));

    snprintf(authorization_header, YADL_MIDIUM_SIZE, context->info.AUTHORIZATION_HEADER, context->info.TOKEN);
    struct http_result *result = http_request("GET", get_self_user, authorization_header, NULL,context->info.APPLICATION, NULL);

    if(result->response_code != 200) {
        self_user_t *self_user = yadl_malloc(sizeof(self_user_t));
        return self_user;
    } else {
        context->self_user = parse_user(json_object_get_wrapping_value(yadl_json_object_builder(*result->response_body)));
        return context->self_user;
    }
}
