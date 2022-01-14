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
#include "impl.h"

audit_log_t *parse_audit_log(JSON_Value *audit_log_value) {
    JSON_Object *audit_log = json_object(audit_log_value);
    audit_log_t *result = yadl_malloc(sizeof(audit_log_t));

    *result = (audit_log_t) { yadl_object_array_parse(YADL_OBJECT_AUDIT_LOG_ENTRY, json_object_get_array(audit_log, "audit_log_entries")),
                              yadl_object_array_parse(YADL_OBJECT_GUILD_SCHEDULED_EVENT, json_object_get_array(audit_log, "guild_scheduled_events")),
                              yadl_object_array_parse(YADL_OBJECT_INTEGRATION, json_object_get_array(audit_log, "integrations")),
                              yadl_object_array_parse(YADL_OBJECT_CHANNEL, json_object_get_array(audit_log, "threads")),
                              yadl_object_array_parse(YADL_OBJECT_USER, json_object_get_array(audit_log, "users")),
                              yadl_object_array_parse(YADL_OBJECT_WEBHOOK, json_object_get_array(audit_log, "webhooks"))
    };

    return result;
}

audit_log_entry_t *parse_audit_log_entry(JSON_Value *audit_log_entry_value) {
    JSON_Object *audit_log_entry = json_object(audit_log_entry_value);
    audit_log_entry_t *result = yadl_malloc(sizeof(audit_log_entry_t));
    *result = (audit_log_entry_t) {(char *) json_object_get_string(audit_log_entry, "target_id"),
                                   yadl_object_array_parse(YADL_OBJECT_AUDIT_LOG_CHANGE, json_object_get_array(audit_log_entry, "changes")),
                                   (char *) json_object_get_string(audit_log_entry, "user_id"),
                                   (char *) json_object_get_string(audit_log_entry, "id"),
                                   (int) json_object_get_number(audit_log_entry, "action_type"),
                                   (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(audit_log_entry, "options"))),
                                   (char *) json_object_get_string(audit_log_entry, "reason")
    };

    return result;
}

audit_log_change_t *parse_audit_log_change(JSON_Value *audit_log_change_value) {
    JSON_Object *audit_log_change = json_object(audit_log_change_value);
    audit_log_change_t *result = yadl_malloc(sizeof(audit_log_change_t));
    *result = (audit_log_change_t) {(char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(audit_log_change, "new_value"))),
                                     (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(audit_log_change, "old_value"))),
                                     (char *) json_object_get_string(audit_log_change, "key")
    };

    return result;
}

JSON_Value *struct_audit_log_change(audit_log_change_t *audit_log_change) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    json_object_set_string(result, "new_value", audit_log_change->new_value);
    json_object_set_string(result, "old_value", audit_log_change->old_value);
    json_object_set_string(result, "key", audit_log_change->key);

    return json_object_get_wrapping_value(result);
}
JSON_Value *struct_audit_log_entry(audit_log_entry_t *audit_log_entry) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    json_object_set_string(result, "target_id", audit_log_entry->target_id);

    JSON_Array *changes = yadl_json_array_builder(NULL);
    for (int i=0; i<audit_log_entry->changes->size; i++)
        json_array_append_value(changes, struct_audit_log_change((audit_log_change_t *)audit_log_entry->changes->array[i]));

    json_object_set_string(result, "user_id", audit_log_entry->user_id);
    json_object_set_string(result, "id", audit_log_entry->id);
    json_object_set_number(result, "action_type", audit_log_entry->action_type);
    json_object_set_string(result, "options", audit_log_entry->options);
    json_object_set_string(result, "reason", audit_log_entry->reason);

    return json_object_get_wrapping_value(result);
}
JSON_Value *struct_audit_log(audit_log_t *audit_log) {
    JSON_Object *result = yadl_json_object_builder(NULL);


    JSON_Array *audit_log_entries = yadl_json_array_builder(NULL);
    for (int i=0; i<audit_log->audit_log_entries->size; i++)
        json_array_append_value(audit_log_entries, struct_audit_log_entry((audit_log_entry_t *)audit_log->audit_log_entries->array[i]));


    JSON_Array *guild_scheduled_events = yadl_json_array_builder(NULL);
    for (int i=0; i<audit_log->guild_scheduled_events->size; i++)
        json_array_append_value(guild_scheduled_events, struct_guild_scheduled_event((guild_scheduled_event_t *)audit_log->guild_scheduled_events->array[i]));


    JSON_Array *integrations = yadl_json_array_builder(NULL);
    for (int i=0; i<audit_log->integrations->size; i++)
        json_array_append_value(integrations, struct_integration((integration_t *)audit_log->integrations->array[i]));


    JSON_Array *threads = yadl_json_array_builder(NULL);
    for (int i=0; i<audit_log->threads->size; i++)
        json_array_append_value(threads, struct_channel((channel_t *)audit_log->threads->array[i]));


    JSON_Array *users = yadl_json_array_builder(NULL);
    for (int i=0; i<audit_log->users->size; i++)
        json_array_append_value(users, struct_user((user_t *)audit_log->users->array[i]));


    JSON_Array *webhooks = yadl_json_array_builder(NULL);
    for (int i=0; i<audit_log->webhooks->size; i++)
        json_array_append_value(webhooks, struct_webhook((webhook_t *)audit_log->webhooks->array[i]));


    return json_object_get_wrapping_value(result);
}
