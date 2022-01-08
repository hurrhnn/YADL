/*
 YADL is Yet Another Discord Library, written from the scratch.
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

#include "utils.h"

char *yadl_strrem(const char *str, const char *sub) {
    char *copy_str = yadl_malloc(strlen(str));
    memcpy(copy_str, str, strlen(str));
    size_t len = strlen(sub);

    if (len > 0) {
        char *p = copy_str;
        while ((p = strstr(p, sub)) != NULL) {
            memmove(p, p + len, strlen(p + len) + 1);
        }
    }
    return copy_str;
}

char *yadl_strcat(const char *str1, const char *str2) {
    char *str = yadl_malloc(strlen(str1) + strlen(str2) + 1);
    memcpy(str, str1, strlen(str1));
    memcpy(str + strlen(str1), str2, strlen(str2) + 1);
    return str;
}

void *yadl_malloc(size_t length, ...) {
    int8_t selected_node = YADL_GC_NODE_ADDRESS;
    va_list ap;

    va_start(ap, length);
    if(va_arg(ap, size_t) == true)
        selected_node = (int8_t) YADL_NON_GC_NODE;

    void *address = malloc(length);
    memset(address, 0x0, length);

    yadl_gc_append(address, selected_node);
    va_end(ap);
    return address;
}

void *yadl_realloc(void *address, size_t length) {
    void *new_address = realloc(address, length);
    if (address != new_address) {
        delete_node(yadl_gc_get_context(YADL_GC_NODE_ADDRESS), address,
                    YADL_GC_NODE_ADDRESS); // address is already free'd by realloc().
        yadl_gc_append(new_address, YADL_GC_NODE_ADDRESS);
    }
    return new_address;
}
