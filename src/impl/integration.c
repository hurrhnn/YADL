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
    integration_t *result = yadl_malloc(sizeof(integration_t));

    *result = (integration_t) {(char *) json_object_get_string(integration, "id"),
                               (char *) json_object_get_string(integration, "name"),
                               (char *) json_object_get_string(integration, "type"),
                               yadl_json_boolean_null_check(json_object_get_boolean(integration, "enabled")),
                               yadl_json_boolean_null_check(json_object_get_boolean(integration, "syncing")),
                               (char *) json_object_get_string(integration, "role_id"),
                               yadl_json_boolean_null_check(json_object_get_boolean(integration, "enable_emoticons")),
                               (int) json_object_get_number(integration, "expire_behavior"),
                               (int) json_object_get_number(integration, "expire_grace_period "),
                               parse_user(json_object_get_wrapping_value(json_object_get_object(integration, "user"))),
                               parse_integration_account(json_object_get_wrapping_value(json_object_get_object(integration, "account"))),
                               (char *) json_object_get_string(integration, "synced_at"),
                               (int) json_object_get_number(integration, "subscriber_count"),
                               yadl_json_boolean_null_check(json_object_get_boolean(integration, "revoked")),
                               parse_application(json_object_get_wrapping_value(json_object_get_object(integration, "application")))
    };

    return result;
}

integration_account_t *parse_integration_account(JSON_Value *integration_account_value) {
    JSON_Object *integration_account = json_object(integration_account_value);
    integration_account_t *result = yadl_malloc(sizeof(integration_account_t));

    *result = (integration_account_t) {(char *) json_object_get_string(integration_account, "id"),
                                       (char *) json_object_get_string(integration_account, "name")
    };

    return result;
}

integration_application_t *parse_integration_application(JSON_Value *integration_application_value) {
    JSON_Object *integration_application = json_object(integration_application_value);
    integration_application_t *result = yadl_malloc(sizeof(integration_application_t));

    *result = (integration_application_t) {(char *) json_object_get_string(integration_application, "id"),
                                           (char *) json_object_get_string(integration_application, "name"),
                                           (char *) json_object_get_string(integration_application, "icon"),
                                           (char *) json_object_get_string(integration_application, "description"),
                                           (char *) json_object_get_string(integration_application, "summary"),
                                           parse_user(json_object_get_wrapping_value(json_object_get_object(integration_application, "bot")))
    };

    return result;
}

JSON_Value *struct_integration_application(integration_application_t *integration_application) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    json_object_set_string(result, "id", integration_application->id);
    json_object_set_string(result, "name", integration_application->name);
    json_object_set_string(result, "icon", integration_application->icon);
    json_object_set_string(result, "description", integration_application->description);
    json_object_set_string(result, "summary", integration_application->summary);
    json_object_set_value(result, "bot", struct_user(integration_application->bot));

    return json_object_get_wrapping_value(result);
}
JSON_Value *struct_integration_account(integration_account_t *integration_account) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    json_object_set_string(result, "id", integration_account->id);
    json_object_set_string(result, "name", integration_account->name);

    return json_object_get_wrapping_value(result);
}
JSON_Value *struct_integration(integration_t *integration) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    json_object_set_string(result, "id", integration->id);
    json_object_set_string(result, "name", integration->name);
    json_object_set_string(result, "type", integration->type);
    json_object_set_boolean(result, "enabled", integration->enabled);
    json_object_set_boolean(result, "syncing", integration->syncing);
    json_object_set_string(result, "role_id", integration->role_id);
    json_object_set_boolean(result, "enable_emoticons", integration->enable_emoticons);
    json_object_set_number(result, "expire_behavior", integration->expire_behavior);
    json_object_set_number(result, "expire_grace_period ", integration->expire_grace_period );
    json_object_set_value(result, "user", struct_user(integration->user));
    json_object_set_value(result, "account", struct_integration_account(integration->account));
    json_object_set_string(result, "synced_at", integration->synced_at);
    json_object_set_number(result, "subscriber_count", integration->subscriber_count);
    json_object_set_boolean(result, "revoked", integration->revoked);
    json_object_set_value(result, "application", struct_application(integration->application));

    return json_object_get_wrapping_value(result);
}
