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

#include "integration.h"

integration_t *parse_integration(JSON_Value *integration_value) {
    JSON_Object *integration = json_object(integration_value);
    integration_t *result = yadl_malloc(sizeof(integration_t), true);

    *result = (integration_t) {(char *) json_object_get_string(integration, "id"),
                               (char *) json_object_get_string(integration, "name"),
                               (char *) json_object_get_string(integration, "type"),
                               json_object_get_boolean(integration, "enabled"),
                               json_object_get_boolean(integration, "syncing"),
                               (char *) json_object_get_string(integration, "role_id"),
                               json_object_get_boolean(integration, "enable_emoticons"),
                               (char *) json_serialize_to_string(json_object_get_wrapping_value(json_object_get_object(integration, "expire_behavior"))),
                               (int) json_object_get_number(integration, "expire_grace_period "),
                               (char *) json_serialize_to_string(json_object_get_wrapping_value(json_object_get_object(integration, "user"))),
                               (char *) json_serialize_to_string(json_object_get_wrapping_value(json_object_get_object(integration, "account"))),
                               (char *) json_object_get_string(integration, "synced_at"),
                               (int) json_object_get_number(integration, "subscriber_count"),
                               json_object_get_boolean(integration, "revoked"),
                               (char *) json_serialize_to_string(json_object_get_wrapping_value(json_object_get_object(integration, "application")))
    };

    return result;
}

integration_account_t *parse_integration_account(JSON_Value *integration_account_value) {
    JSON_Object *integration_account = json_object(integration_account_value);
    integration_account_t *result = yadl_malloc(sizeof(integration_account_t), true);

    *result = (integration_account_t) {(char *) json_object_get_string(integration_account, "id"),
                                       (char *) json_object_get_string(integration_account, "name ")
    };

    return result;
}

integration_application_t *parse_integration_application(JSON_Value *integration_application_value) {
    JSON_Object *integration_application = json_object(integration_application_value);
    integration_application_t *result = yadl_malloc(sizeof(integration_application_t), true);

    *result = (integration_application_t) {(char *) json_object_get_string(integration_application, "id"),
                                           (char *) json_object_get_string(integration_application, "name"),
                                           (char *) json_object_get_string(integration_application, "icon"),
                                           (char *) json_object_get_string(integration_application, "description"),
                                           (char *) json_object_get_string(integration_application, "summary"),
                                           (char *) json_serialize_to_string(json_object_get_wrapping_value(json_object_get_object(integration_application, "bot")))
    };

    return result;
}
