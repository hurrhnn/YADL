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

#ifndef YADL_AUDIT_LOG_H
#define YADL_AUDIT_LOG_H

#include <stdbool.h>
#include "parson.h"
#include "yadl/utils/utils.h"

typedef struct yadl_object_array yadl_object_array_t;

typedef struct __attribute__((__packed__)) {
    yadl_object_array_t *audit_log_entries;
    /* array of audit log entry objects */
    yadl_object_array_t *guild_scheduled_events;
    /* array of guild scheduled event objects */
    yadl_object_array_t *integrations;
    /* array of partial integration objects */
    yadl_object_array_t *threads;
    /* array of channel objects */
    yadl_object_array_t *users;
    /* array of user objects */
    yadl_object_array_t *webhooks;
    /* array of webhook objects */

} audit_log_t;

typedef struct __attribute__((__packed__)) {
    char *target_id;
    yadl_object_array_t *changes;
    /* array of audit log change objects */
    char *user_id;
    char *id;
    int action_type;
    /* audit log event */
    char *options;
    /* optional audit entry info */
    char *reason;

} audit_log_entry_t;

typedef struct __attribute__((__packed__)) {
    char *new_value;
    char *old_value;
    /* mixed */
    char *key;

} audit_log_change_t;

audit_log_t *parse_audit_log(JSON_Value *audit_log_value);

audit_log_entry_t *parse_audit_log_entry(JSON_Value *audit_log_entry_value);

audit_log_change_t *parse_audit_log_change(JSON_Value *audit_log_change_value);

JSON_Value *struct_audit_log_change(audit_log_change_t *audit_log_change);

JSON_Value *struct_audit_log_entry(audit_log_entry_t *audit_log_entry);

JSON_Value *struct_audit_log(audit_log_t *audit_log);

#endif //YADL_AUDIT_LOG_H
