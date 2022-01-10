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

#ifndef YADL_ATTACHMENT_H
#define YADL_ATTACHMENT_H

#include <stdbool.h>
#include "parson.h"
#include "../utils/utils.h"
#include "../json/json.h"

typedef struct __attribute__((__packed__)) {
    char *filename;
    char *description;
    char *content_type;
    int size;
    char *url;
    char *proxy_url;
    int height;
    int width;
    bool ephemeral;

} attachment_t;

attachment_t *parse_attachment(JSON_Value *attachment_value);

#endif //YADL_ATTACHMENT_H
