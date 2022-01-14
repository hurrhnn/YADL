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

#ifndef YADL_RETRIEVE_APPLICATION_INFO_H
#define YADL_RETRIEVE_APPLICATION_INFO_H

#include "../utils/utils.h"
#include "../http/http_request.h"
#include "../impl/impl.h"
#include "../yadl.h"

#define YADL_RETRIEVE_APPLICATION_INFO "/oauth2/applications/@me"

application_t *yadl_retrieve_application_info(yadl_context_t *context);

#endif //YADL_RETRIEVE_APPLICATION_INFO_H
