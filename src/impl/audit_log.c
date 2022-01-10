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

#include "audit_log.h"

audit_log_t *parse_audit_log(JSON_Value *audit_log_value) {
    JSON_Object *audit_log = json_object(audit_log_value);
    audit_log_t *result = yadl_malloc(sizeof(audit_log_t), true);
    *result = (audit_log_t) {(char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(audit_log, "audit_log_entries"))),
                             (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(audit_log, "guild_scheduled_events"))),
                             (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(audit_log, "integrations"))),
                             (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(audit_log, "threads"))),
                             (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(audit_log, "users"))),
                             (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(audit_log, "webhooks")))
    };

    return result;
}

audit_log_entry_t *parse_audit_log_entry(JSON_Value *audit_log_entry_value) {
    JSON_Object *audit_log_entry = json_object(audit_log_entry_value);
    audit_log_entry_t *result = yadl_malloc(sizeof(audit_log_entry_t), true);
    *result = (audit_log_entry_t) {(char *) json_object_get_string(audit_log_entry, "target_id"),
                                   (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(audit_log_entry, "changes"))),
                                   (char *) json_object_get_string(audit_log_entry, "user_id"),
                                   (char *) json_object_get_string(audit_log_entry, "id"),
                                   (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(audit_log_entry, "action_type"))),
                                   (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(audit_log_entry, "options"))),
                                   (char *) json_object_get_string(audit_log_entry, "reason")
    };

    return result;
}

audit_log_change_t *parse_audit_log_change(JSON_Value *audit_log_change_value) {
    JSON_Object *audit_log_change = json_object(audit_log_change_value);
    audit_log_change_t *result = yadl_malloc(sizeof(audit_log_change_t), true);
    *result = (audit_log_change_t) {(char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(audit_log_change, "old_value"))),
                                    (char *) json_object_get_string(audit_log_change, "key")
    };

    return result;
}
