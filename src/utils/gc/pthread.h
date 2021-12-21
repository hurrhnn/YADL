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

#ifndef YADL_PTHREAD_H
#define YADL_PTHREAD_H

#define _GNU_SOURCE
#define __USE_GNU

#include <signal.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../utils.h"

typedef struct yadl_pthread_context {
    pthread_t *pthread;
    pthread_attr_t *pthread_attr;
    pthread_mutex_t *pthread_mutex;
    pthread_cond_t *pthread_cond;
} yadl_pthread_context_t;

void *yadl_pthread_create(void *function, pthread_attr_t *pthread_attr, void *args);

void yadl_pthread_append(pthread_t pthread);

void yadl_thread_remove(yadl_pthread_context_t *pthread_context);

#endif
