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

/*
 Simple *char-key Linked List Implementation
 Copyright (C) 2021 Wonjun Jung (KokoseiJ), Rhnn Hur (hurrhnn)
*/

#ifndef YADL_LINKED_LIST_H
#define YADL_LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "yadl/utils/utils.h"

typedef struct obj_list{
    char *key;
    void *value;
    struct obj_list *next;
} obj_list_t;

obj_list_t *put_list(size_t type, obj_list_t *list, char *key, void *value);

void *get_list(obj_list_t *list, char *key);

void free_list(obj_list_t *list);

#endif //YADL_LINKED_LIST_H
