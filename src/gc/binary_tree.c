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
 Simple Binary Tree Implementation
 Copyright (C) 2021 Wonjun Jung (KokoseiJ), Rhnn Hur (hurrhnn)
*/

#include "binary_tree.h"
#include "../gc/gc.h"

#if __linux__
pthread_mutex_t node_mutex = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;
#else /* pho`six Y E A H */
pthread_mutex_t node_mutex = PTHREAD_RECURSIVE_MUTEX_INITIALIZER;
#endif

gc_node_t *insert_node(gc_node_t *gc_node, void *address) {
    pthread_mutex_lock(&node_mutex);
    gc_node_t *new_node, **target, *return_value = NULL;

    if (gc_node == NULL) {
        new_node = malloc(sizeof(gc_node_t));
        *new_node = (gc_node_t) {address, 0x0, NULL, NULL, NULL};
        return_value = new_node;
    } else {
        if (address < gc_node->address)
            target = &gc_node->left;
        else
            target = &gc_node->right;

        *target = insert_node(*target, address);
        (*target)->parent = gc_node;
        return_value = gc_node;
    }
    pthread_mutex_unlock(&node_mutex);
    return return_value;
}

u_int8_t delete_node(gc_node_t *gc_node, void *address, int8_t node) {
    pthread_mutex_lock(&node_mutex);

    gc_node_t *entry = NULL, **prev_pos = NULL, *target = NULL;
    entry = search_node(gc_node, address, node);

    if (entry == NULL) {
        pthread_mutex_unlock(&node_mutex);
        return 1;
    }

    if (entry->parent->left == entry) prev_pos = &entry->parent->left;
    else prev_pos = &entry->parent->right;

    int case_val;
    case_val = (entry->left != NULL) + (entry->right != NULL);

    switch (case_val) {
        case 0:
            free(gc_node);
            *prev_pos = NULL;
            break;
        case 1:
            if (entry->left != NULL) target = entry->left;
            else target = entry->right;

            *prev_pos = target;
            target->parent = entry->parent;

            free(entry);
            break;
        case 2:
            target = entry->right;
            while (target->left != NULL) target = target->left;

            entry->address = target->address;
            entry->mark = target->mark;

            delete_node(target, target->address, node);
            break;
        default:
            break;

    }

    pthread_mutex_unlock(&node_mutex);
    return 0;
}

gc_node_t *search_node(gc_node_t *gc_node, void *address, int8_t node) {
    pthread_mutex_lock(&node_mutex);
    gc_node_t *result = NULL, *return_value = NULL;
    if (address == NULL || gc_node == NULL) {
        return_value = NULL;
    } else {
        if (node == YADL_GC_NODE_PTHREAD) {
            if (*((yadl_pthread_context_t *) address)->pthread ==
                *((yadl_pthread_context_t *) gc_node->address)->pthread) {
                return_value = gc_node;
            } else if (*((yadl_pthread_context_t *) address)->pthread <
                       *((yadl_pthread_context_t *) gc_node->address)->pthread) {
                result = gc_node->left;
            } else if (*((yadl_pthread_context_t *) gc_node->address)->pthread <
                       *((yadl_pthread_context_t *) address)->pthread) {
                result = gc_node->right;
            }
        } else {
            if (address == gc_node->address)
                return_value = gc_node;
            else if (address < gc_node->address)
                result = gc_node->left;

            else if (gc_node->address < address)
                result = gc_node->right;
        }
        if (return_value == NULL)
            return_value = search_node(result, address, node);
    }

    pthread_mutex_unlock(&node_mutex);
    return return_value;
}

void scan_node(gc_node_t *main_node, gc_node_t *sub_node, int8_t node) {
    pthread_mutex_lock(&node_mutex);

    if (main_node->left != NULL)
        scan_node(main_node->left, sub_node, node);

    if (node == YADL_GC_NODE_PTHREAD) {
        if (pthread_kill(*((yadl_pthread_context_t *) main_node->address)->pthread, 0) != 0) { // if target thread was dead
            yadl_thread_remove(main_node->address);
            delete_node(main_node, main_node->address, node);
        } else {
#if __linux__
            pthread_attr_t pthread_attr;
            void *pthread_stack;
            size_t pthread_stack_size;

            pthread_getattr_np(*((yadl_pthread_context_t *) main_node->address)->pthread, &pthread_attr);
            pthread_attr_getstack(&pthread_attr, &pthread_stack, &pthread_stack_size);

            for (void *i = pthread_stack; i <= pthread_stack + pthread_stack_size; i += sizeof(void *)) {
                gc_node_t *address_node = search_node(sub_node, *(void **) i, YADL_GC_NODE_ADDRESS);
                if (i != NULL && *(void **) i != NULL && address_node != NULL) {
                    if (*(void **) i == address_node->address)
                        address_node->mark = true;
                }
#else
            void *pthread_stack = pthread_get_stackaddr_np(
                    *((yadl_pthread_context_t *) main_node->address)->pthread);
            size_t pthread_stack_size = pthread_get_stacksize_np(
                    *((yadl_pthread_context_t *) main_node->address)->pthread);

            for (void *i = pthread_stack - sizeof(void *);
                 i >= pthread_stack - pthread_stack_size; i -= sizeof(void *)) {
                gc_node_t *address_node = search_node(sub_node, *(void **) i, YADL_GC_NODE_ADDRESS);
                if (i != NULL && *(void **) i != NULL && address_node != NULL && *(void **) i == address_node->address)
                    address_node->mark = true;
#endif
            }
        }
    } else {
        if (main_node->address != NULL) {
            if (!main_node->mark) {
                delete_node(main_node, main_node->address, node);
            } else
                main_node->mark = (int8_t) (main_node->mark == -1 ? main_node->mark : false);
        }
    }

    if (main_node->right != NULL)
        scan_node(main_node->right, sub_node, node);

    pthread_mutex_unlock(&node_mutex);
}

void free_node(gc_node_t *node) {
    pthread_mutex_lock(&node_mutex);
    if (node->left != NULL)
        free_node(node->left);

    if (node->right != NULL)
        free_node(node->right);

    free(node);
    pthread_mutex_unlock(&node_mutex);
}
