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

#ifndef YADL_UTILS_H
#define YADL_UTILS_H

#include <stdlib.h>
#include <strings.h>
#include <libwebsockets.h>

#define YADL_SMALL_SIZE  0x10
#define YADL_MIDIUM_SIZE 0x100
#define YADL_LARGE_SIZE  0x1000

char *yadl_strrem(const char *str, const char *sub);

char *yadl_strcat(const char *str1, const char *str2);

void *yadl_malloc(size_t length);

void *yadl_realloc(void *address, size_t length);

#endif //YADL_STRINGS_H
