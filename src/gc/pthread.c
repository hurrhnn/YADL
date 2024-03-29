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

#include <yadl/gc/pthread.h>
#include <yadl/gc/gc.h>

void *yadl_pthread_create(void *function, pthread_attr_t *pthread_attr, void *args) {
    if(!function)
        return NULL;

    yadl_pthread_context_t *pthread_context = yadl_malloc(sizeof(yadl_pthread_context_t), true);
    if(pthread_attr == NULL) {
        pthread_attr = yadl_malloc(sizeof(pthread_attr_t));
        pthread_attr_init(pthread_attr);
    }
    *pthread_context = (yadl_pthread_context_t) {yadl_malloc(sizeof(pthread_t)),
                                                 pthread_attr,
                                                 yadl_malloc(sizeof(pthread_mutex_t)),
                                                 yadl_malloc(sizeof(pthread_cond_t))};

    pthread_mutex_init(pthread_context->pthread_mutex, NULL);
    pthread_cond_init(pthread_context->pthread_cond, NULL);

    pthread_attr_setstacksize(pthread_context->pthread_attr, YADL_LARGE_SIZE * 1000);
    pthread_create(pthread_context->pthread, pthread_context->pthread_attr, function, args);

    if (yadl_gc_get_context(YADL_GC_NODE_PTHREAD) != NULL)
        yadl_gc_append(pthread_context, YADL_GC_NODE_PTHREAD);

    pthread_attr_destroy(pthread_attr);
    return pthread_context;
}

void yadl_pthread_append(pthread_t pthread) {
    yadl_pthread_context_t *pthread_context = yadl_malloc(sizeof(yadl_pthread_context_t), true);
    *pthread_context = (yadl_pthread_context_t) {yadl_malloc(sizeof(pthread_t), true), NULL, NULL, NULL};
    memcpy(pthread_context->pthread, &pthread, sizeof(pthread_t));
    yadl_gc_append(pthread_context, YADL_GC_NODE_PTHREAD);
}
