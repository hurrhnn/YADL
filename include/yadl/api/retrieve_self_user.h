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

#ifndef YADL_RETRIEVE_SELF_USER_H
#define YADL_RETRIEVE_SELF_USER_H

#include "yadl/utils/utils.h"
#include "yadl/http/http_request.h"
#include "yadl/impl/impl.h"
#include "yadl.h"

#define YADL_RETRIEVE_CURRENT_USER_PATH "/users/@me"

self_user_t *yadl_retrieve_self_user(yadl_context_t *context);

#endif //YADL_RETRIEVE_SELF_USER_H
