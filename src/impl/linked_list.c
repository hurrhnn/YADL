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

#include "linked_list.h"
#include "impl.h"

obj_list_t *put_list(size_t type, obj_list_t *list, char *key, void *value) {
    if (list == NULL) {
        list = yadl_malloc(sizeof(obj_list_t), true);
        *list = (obj_list_t) { key, value, NULL };
        return list;
    }

    if (!strcmp(key, list->key)) {
//        yadl_free(list->value, true);
        list->value = yadl_object_overridable(type) ? yadl_object_override(list, key, value, yadl_get_object_metadata(type)) : value;
    } else
        list->next = put_list(type, list->next, key, value);

    return list;
}

void *get_list(obj_list_t *list, char *key) {
    if (list == NULL) return NULL;

    if (!strcmp(key, list->key))
        return list->value;
    else
        return get_list(list->next, key);
}

void free_list(obj_list_t *list) {
    if (list != NULL) {
        free_list(list->next);
        yadl_free(list->value, true);
        yadl_free(list, true);
    }
}
