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

#ifndef YADL_THREAD_H
#define YADL_THREAD_H

#include <stdbool.h>
#include <parson.h>
#include <yadl/utils/utils.h>
#include <yadl/json/json.h>

typedef struct __attribute__((__packed__)) {
    bool archived;
    int auto_archive_duration;
    char *archive_timestamp;
    bool locked;
    bool invitable;

} thread_metadata_t;

typedef struct __attribute__((__packed__)) {
    char *id;
    char *user_id;
    char *join_timestamp;
    int flags;

} thread_member_t;


thread_metadata_t *parse_thread_metadata(JSON_Value *thread_metadata_value);

thread_member_t *parse_thread_member(JSON_Value *thread_member_value);

JSON_Value *struct_thread_member(thread_member_t *thread_member);

JSON_Value *struct_thread_metadata(thread_metadata_t *thread_metadata);

#endif //YADL_THREAD_H
