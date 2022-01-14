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

#include "gc.h"

void yadl_gc_init() {
    yadl_gc_context_t.non_gc_node = insert_node(NULL, yadl_malloc(sizeof(void *), true));
    yadl_gc_context_t.pthread_context = yadl_malloc(sizeof(yadl_pthread_context_t), true);
    yadl_gc_context_t.pthread_context->pthread_mutex = yadl_malloc(sizeof(pthread_mutex_t), true);

    pthread_mutexattr_t *mutex_attr = yadl_malloc(sizeof(pthread_mutexattr_t), true);
    pthread_mutexattr_init(mutex_attr);
    pthread_mutexattr_settype(mutex_attr, PTHREAD_MUTEX_RECURSIVE);
    pthread_mutex_init(yadl_gc_context_t.pthread_context->pthread_mutex, mutex_attr);

    yadl_gc_set_alive(true);
    yadl_gc_context_t.address_node = insert_node(NULL,
                                                 yadl_malloc(sizeof(void *), true));
    yadl_gc_context_t.address_node->mark = -1; // Do not allow garbage collectors to remove root nodes.

    yadl_gc_context_t.pthread_node = insert_node(NULL,yadl_pthread_create(yadl_gc_loop, NULL, NULL));
}

void *yadl_gc_get_context(int8_t value) {
    switch (value) {
        case YADL_NON_GC_NODE:
            return yadl_gc_context_t.non_gc_node;
        case YADL_GC_NODE_ADDRESS:
            return yadl_gc_context_t.address_node;
        case YADL_GC_NODE_PTHREAD:
            return yadl_gc_context_t.pthread_node;
        default:
            return NULL;
    }
}

void yadl_gc_set_alive(bool alive) {
    yadl_gc_context_t.gc_alive = alive;
}

void yadl_gc_append(void *address, int8_t node) {
    void *selected_node = yadl_gc_get_context(node);
    if (search_node(selected_node, address, node) == NULL) {
        insert_node(selected_node, address);
    }
}

void *yadl_gc_loop() {
    while (yadl_gc_context_t.gc_alive) {
        sleep(1);
        scan_node(yadl_gc_context_t.pthread_node, yadl_gc_context_t.address_node,
                  YADL_GC_NODE_PTHREAD); // mark

        scan_node(yadl_gc_context_t.address_node, NULL,
                  YADL_GC_NODE_ADDRESS); // sweep
    }
    return NULL;
}
