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

#include "invite.h"

invite_t *parse_invite(JSON_Value *invite_value) {
    JSON_Object *invite = json_object(invite_value);
    invite_t *result = yadl_malloc(sizeof(invite_t), true);

    *result = (invite_t) {(char *) json_object_get_string(invite, "code"),
                          (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(invite, "guild"))),
                          (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(invite, "channel"))),
                          (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(invite, "inviter"))),
                          (int) json_object_get_number(invite, "target_type"),
                          (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(invite, "target_user"))),
                          (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(invite, "target_application"))),
                          (int) json_object_get_number(invite, "approximate_presence_count"),
                          (int) json_object_get_number(invite, "approximate_member_count"),
                          (char *) json_object_get_string(invite, "expires_at"),
                          (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(invite, "stage_instance"))),
                          (char *) json_serialize_to_string_pretty(json_object_get_wrapping_value(json_object_get_object(invite, "guild_scheduled_event")))
    };

    return result;
}

invite_metadata_t *parse_invite_metadata(JSON_Value *invite_metadata_value) {
    JSON_Object *invite_metadata = json_object(invite_metadata_value);
    invite_metadata_t *result = yadl_malloc(sizeof(invite_metadata_t), true);

    *result = (invite_metadata_t) {(int) json_object_get_number(invite_metadata, "uses"),
                                   (int) json_object_get_number(invite_metadata, "max_uses"),
                                   (int) json_object_get_number(invite_metadata, "max_age"),
                                   yadl_json_boolean_null_check(json_object_get_boolean(invite_metadata, "temporary")),
                                   (char *) json_object_get_string(invite_metadata, "created_at")
    };

    return result;
}

invite_stage_instance_t *parse_invite_stage_instance(JSON_Value *invite_stage_instance_value) {
    JSON_Object *invite_stage_instance = json_object(invite_stage_instance_value);
    invite_stage_instance_t *result = yadl_malloc(sizeof(invite_stage_instance_t), true);

    *result = (invite_stage_instance_t) {(char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(invite_stage_instance, "members"))),
                                         (int) json_object_get_number(invite_stage_instance, "participant_count"),
                                         (int) json_object_get_number(invite_stage_instance, "speaker_count"),
                                         (char *) json_object_get_string(invite_stage_instance, "topic")
    };

    return result;
}



stage_instance_t *parse_stage_instance(JSON_Value *stage_instance_value) {
    JSON_Object *stage_instance = json_object(stage_instance_value);
    stage_instance_t *result = yadl_malloc(sizeof(stage_instance_t), true);

    *result = (stage_instance_t) {(char *) json_object_get_string(stage_instance, "id"),
                                  (char *) json_object_get_string(stage_instance, "guild_id"),
                                  (char *) json_object_get_string(stage_instance, "channel_id"),
                                  (char *) json_object_get_string(stage_instance, "topic"),
                                  (int) json_object_get_number(stage_instance, "privacy_level"),
                                  yadl_json_boolean_null_check(json_object_get_boolean(stage_instance, "discoverable_disabled"))
    };

    return result;
}
