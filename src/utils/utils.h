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

#include "info.h"

#define YADL_SMALL_SIZE  0x10
#define YADL_MIDIUM_SIZE 0x100
#define YADL_LARGE_SIZE  0x1000

#define YADL_SET_VALUE_IF_NULL(var, value) var = ((var) == 0 ? (var) = (value) : (var))

#ifdef _WIN32
    #define YADL_CLIENT_OS "Windows 32-bit"
#elif _WIN64
    #define YADL_CLIENT_OS "Windows 64-bit"
#elif __APPLE__ || __MACH__
    #define YADL_CLIENT_OS "Mac OS X"
#elif __linux__
    #define YADL_CLIENT_OS "Linux";
#elif __FreeBSD__
    #define YADL_CLIENT_OS "FreeBSD"
#elif __unix || __unix__
    #define YADL_CLIENT_OS "Unix"
#else
    #define YADL_CLIENT_OS "Other"
#endif

char *yadl_strrem(const char *str, const char *sub);

char *yadl_strcat(const char *str1, const char *str2);

void *yadl_malloc(size_t length, ...);

void *yadl_realloc(void *address, size_t length);

void yadl_free(void* address, ...);

size_t yadl_get_file_size(FILE* fp);

char* yadl_get_file_name_from_path(char* path);

#endif //YADL_STRINGS_H
