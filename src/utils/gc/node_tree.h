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

#ifndef YADL_NODE_TREE_H
#define YADL_NODE_TREE_H

#include "pthread.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct gc_node {
    void *address;
    int8_t mark;
    struct gc_node *left, *right, *parent;
} gc_node_t;

gc_node_t *insert_node(gc_node_t *gc_node, void *address);

u_int8_t delete_node(gc_node_t *gc_node, void *address, int8_t node);

gc_node_t *search_node(gc_node_t *gc_node, void *address, int8_t node);

void scan_node(gc_node_t *main_node, gc_node_t *sub_node, int8_t node);

void free_node(gc_node_t *node);

#endif //YADL_BINARY_TREE_H
