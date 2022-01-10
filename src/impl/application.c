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

#include "application.h"

application_t *parse_application(JSON_Value *application_value) {
    JSON_Object *application = json_object(application_value);
    application_t *result = yadl_malloc(sizeof(application_t), true);
    *result = (application_t) {(char *) json_object_get_string(application, "id"),
                               (char *) json_object_get_string(application, "name"),
                               (char *) json_object_get_string(application, "icon"),
                               (char *) json_object_get_string(application, "description"),
                               (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(application, "rpc_origins"))),
                               yadl_json_boolean_null_check(json_object_get_boolean(application, "bot_public")),
                               yadl_json_boolean_null_check(json_object_get_boolean(application, "bot_require_code_grant")),
                               (char *) json_object_get_string(application, "terms_of_service_url"),
                               (char *) json_object_get_string(application, "privacy_policy_url"),
                               (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(application, "owner"))),
                               (char *) json_object_get_string(application, "summary"),
                               (char *) json_object_get_string(application, "verify_key"),
                               (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(application, "team"))),
                               (char *) json_object_get_string(application, "guild_id"),
                               (char *) json_object_get_string(application, "primary_sku_id"),
                               (char *) json_object_get_string(application, "slug"),
                               (char *) json_object_get_string(application, "cover_image"),
                               (int) json_object_get_number(application, "flags")
    };

    return result;
}
