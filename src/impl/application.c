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
#include "impl.h"

application_t *parse_application(JSON_Value *application_value) {
    JSON_Object *application = json_object(application_value);
    application_t *result = yadl_malloc(sizeof(application_t));

    *result = (application_t) {(char *) json_object_get_string(application, "id"),
                               (char *) json_object_get_string(application, "name"),
                               (char *) json_object_get_string(application, "icon"),
                               (char *) json_object_get_string(application, "description"),
                               (char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(application, "rpc_origins"))),
                               yadl_json_boolean_null_check(json_object_get_boolean(application, "bot_public")),
                               yadl_json_boolean_null_check(json_object_get_boolean(application, "bot_require_code_grant")),
                               (char *) json_object_get_string(application, "terms_of_service_url"),
                               (char *) json_object_get_string(application, "privacy_policy_url"),
                               parse_user(json_object_get_wrapping_value(json_object_get_object(application, "owner"))),
                               (char *) json_object_get_string(application, "summary"),
                               (char *) json_object_get_string(application, "verify_key"),
                               parse_team(json_object_get_wrapping_value(json_object_get_object(application, "team"))),
                               (char *) json_object_get_string(application, "guild_id"),
                               (char *) json_object_get_string(application, "primary_sku_id"),
                               (char *) json_object_get_string(application, "slug"),
                               (char *) json_object_get_string(application, "cover_image"),
                               (int) json_object_get_number(application, "flags")
    };

    return result;
}

team_t *parse_team(JSON_Value *team_value) {
    JSON_Object *team = json_object(team_value);
    team_t *result = yadl_malloc(sizeof(team_t));

    *result = (team_t) {(char *) json_object_get_string(team, "icon"),
                        (char *) json_object_get_string(team, "id"),
                        yadl_object_array_parse(YADL_OBJECT_TEAM_MEMBER, json_object_get_array(team, "members")),
                        (char *) json_object_get_string(team, "name"),
                        (char *) json_object_get_string(team, "owner_user_id")
    };

    return result;
}

team_member_t *parse_team_member(JSON_Value *team_member_value) {
    JSON_Object *team_member = json_object(team_member_value);
    team_member_t *result = yadl_malloc(sizeof(team_member_t));

    *result = (team_member_t) {(int) json_object_get_number(team_member, "membership_state"),
                               (char *) json_object_get_string(team_member, "team_id"),
                               parse_user(json_object_get_wrapping_value(json_object_get_object(team_member, "user")))
    };

    return result;
}

JSON_Value *struct_team_member(team_member_t *team_member) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    json_object_set_number(result, "membership_state", team_member->membership_state);
    json_object_set_string(result, "team_id", team_member->team_id);
    json_object_set_value(result, "user", struct_user(team_member->user));

    return json_object_get_wrapping_value(result);
}
JSON_Value *struct_team(team_t *team) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    json_object_set_string(result, "icon", team->icon);
    json_object_set_string(result, "id", team->id);

    JSON_Array *members = yadl_json_array_builder(NULL);
    for (int i=0; i<team->members->size; i++)
        json_array_append_value(members, struct_team_member((team_member_t *)team->members->array[i]));

    json_object_set_string(result, "name", team->name);
    json_object_set_string(result, "owner_user_id", team->owner_user_id);

    return json_object_get_wrapping_value(result);
}
JSON_Value *struct_application(application_t *application) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    json_object_set_string(result, "id", application->id);
    json_object_set_string(result, "name", application->name);
    json_object_set_string(result, "icon", application->icon);
    json_object_set_string(result, "description", application->description);
    json_object_set_string(result, "rpc_origins", application->rpc_origins);
    json_object_set_boolean(result, "bot_public", application->bot_public);
    json_object_set_boolean(result, "bot_require_code_grant", application->bot_require_code_grant);
    json_object_set_string(result, "terms_of_service_url", application->terms_of_service_url);
    json_object_set_string(result, "privacy_policy_url", application->privacy_policy_url);
    json_object_set_value(result, "owner", struct_user(application->owner));
    json_object_set_string(result, "summary", application->summary);
    json_object_set_string(result, "verify_key", application->verify_key);
    json_object_set_value(result, "team", struct_team(application->team));
    json_object_set_string(result, "guild_id", application->guild_id);
    json_object_set_string(result, "primary_sku_id", application->primary_sku_id);
    json_object_set_string(result, "slug", application->slug);
    json_object_set_string(result, "cover_image", application->cover_image);
    json_object_set_number(result, "flags", application->flags);

    return json_object_get_wrapping_value(result);
}
