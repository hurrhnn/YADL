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

#include "impl.h"
#include "../yadl.h"

void yadl_object_init(yadl_context_t *context) {
    context->guilds = put_list(YADL_OBJECT_GUILD, NULL, "", NULL);
    context->users = put_list(YADL_OBJECT_USER, NULL, "", NULL);
}

bool yadl_object_overridable(size_t type) {
    switch (type) {
        case YADL_OBJECT_USER:
            return true;
        default:
            return false;
    }
}

void *yadl_object_override(obj_list_t *list, char* key, void* object, yadl_object_metadata_t *metadata) {
    size_t struct_size = 0, current_size = 0, idx = 0;
    for(int i = 0; i < strlen(metadata->member_size); i++)
        struct_size += metadata->member_size[i] - '0';

    void *exist_object = get_list(list, key), *new_object = yadl_malloc(struct_size, true);
    while(true) {
        if(struct_size == current_size)
            break;
        size_t member_size = metadata->member_size[idx++] - '0';
        int64_t exist_data, override_data;

        memset(&exist_data, 0x0, sizeof(int64_t));
        memset(&override_data, 0x0, sizeof(int64_t));

        memcpy(&exist_data, exist_object + current_size, member_size);
        memcpy(&override_data, object + current_size, member_size);
        current_size += member_size;

        if(exist_data == 0x0 || exist_data != override_data)
            exist_data = override_data;

        memcpy(new_object, exist_object + current_size, member_size);
    }

    return new_object;
}
