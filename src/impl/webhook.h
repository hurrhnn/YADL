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

#ifndef YADL_WEBHOOK_H
#define YADL_WEBHOOK_H

#include "parson.h"
#include "../utils/utils.h"

typedef struct __attribute__((__packed__)) {
    char *id;
    int type;
    char *guild_id;
    char *channel_id;
    char *user;
    /* user object */
    char *name;
    char *avatar;
    char *token;
    char *application_id;
    char *source_guild;
    /* partial guild object */
    char *source_channel;
    /* partial channel object */
    char *url;

} webhook_t;

webhook_t *parse_webhook(JSON_Value *webhook_value);

#endif //YADL_WEBHOOK_H
