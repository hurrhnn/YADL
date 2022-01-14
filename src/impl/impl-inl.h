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

#ifndef YADL_IMPL_INL_H
#define YADL_IMPL_INL_H

#include <parson.h>
#include <stdbool.h>
#include <stddef.h>
#include "linked_list.h"

typedef struct yadl_context yadl_context_t;
typedef struct yadl_object_metadata yadl_object_metadata_t;
typedef struct yadl_object_array yadl_object_array_t;

bool yadl_object_overridable(size_t type);

void *yadl_object_override(obj_list_t *list, char* key, void* object, yadl_object_metadata_t *metadata);

void yadl_object_init(yadl_context_t *context);

yadl_object_array_t *yadl_object_array_parse(size_t type, JSON_Array *json_array);

#endif //YADL_IMPL_INL_H
