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
#include "../utils/utils.h"

typedef struct yadl_audit_log {
    char *audit_log_entries;
    /* array of audit log entry objects */
    char *guild_scheduled_events;
    /* array of guild scheduled event objects */
    char *integrations;
    /* array of partial integration objects */
    char *threads;
    /* array of channel objects */
    char *users;
    /* array of user objects */
    char *webhooks;
    /* array of webhook objects */

} audit_log_t;

typedef struct yadl_audit_log_entry {
    char *target_id;
    char *changes;
    /* array of audit log change objects */
    char *user_id;
    char *id;
    char *action_type;
    /* audit log event */
    char *options;
    /* optional audit entry info */
    char *reason;

} audit_log_entry_t;

typedef struct yadl_audit_log_change {
    char *old_value;
    /* mixed */
    char *key;

} audit_log_change_t;

#endif //YADL_AUDIT_LOG_H
