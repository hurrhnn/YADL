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

#ifndef YADL_GC_H
#define YADL_GC_H

#define YADL_NON_GC_NODE 0xFFFFFFFF
#define YADL_GC_NODE_ADDRESS 0x0
#define YADL_GC_NODE_PTHREAD 0x1

#include <stdbool.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include "parson.h"

#include <yadl/gc/binary_tree.h>
#include <yadl/gc/pthread.h>

typedef struct gc_node gc_node_t;
typedef struct yadl_pthread_context yadl_pthread_context_t;

static struct yadl_gc_context {
    bool gc_alive;
    gc_node_t *address_node;
    gc_node_t *pthread_node;

    gc_node_t *non_gc_node;
    yadl_pthread_context_t *pthread_context;
} yadl_gc_context_t;

void yadl_gc_init();

void yadl_gc_set_alive(bool alive);

void* yadl_gc_get_context(int8_t value);

void yadl_gc_append(void *address, int8_t node);

void *yadl_gc_loop();

#endif
