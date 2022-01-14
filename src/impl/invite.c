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
    invite_t *result = yadl_malloc(sizeof(invite_t));

    *result = (invite_t) {(char *) json_object_get_string(invite, "code"),
                          parse_guild(json_object_get_wrapping_value(json_object_get_object(invite, "guild"))),
                          parse_channel(json_object_get_wrapping_value(json_object_get_object(invite, "channel"))),
                          parse_user(json_object_get_wrapping_value(json_object_get_object(invite, "inviter"))),
                          (int) json_object_get_number(invite, "target_type"),
                          parse_user(json_object_get_wrapping_value(json_object_get_object(invite, "target_user"))),
                          parse_application(json_object_get_wrapping_value(json_object_get_object(invite, "target_application"))),
                          (int) json_object_get_number(invite, "approximate_presence_count"),
                          (int) json_object_get_number(invite, "approximate_member_count"),
                          (char *) json_object_get_string(invite, "expires_at"),
                          parse_invite_stage_instance(json_object_get_wrapping_value(json_object_get_object(invite, "stage_instance"))),
                          parse_guild_scheduled_event(json_object_get_wrapping_value(json_object_get_object(invite, "guild_scheduled_event")))
    };

    return result;
}

invite_metadata_t *parse_invite_metadata(JSON_Value *invite_metadata_value) {
    JSON_Object *invite_metadata = json_object(invite_metadata_value);
    invite_metadata_t *result = yadl_malloc(sizeof(invite_metadata_t));

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
    invite_stage_instance_t *result = yadl_malloc(sizeof(invite_stage_instance_t));

    *result = (invite_stage_instance_t) {(char *) json_serialize_to_string_pretty(json_array_get_wrapping_value(json_object_get_array(invite_stage_instance, "members"))),
                                         (int) json_object_get_number(invite_stage_instance, "participant_count"),
                                         (int) json_object_get_number(invite_stage_instance, "speaker_count"),
                                         (char *) json_object_get_string(invite_stage_instance, "topic")
    };

    return result;
}



stage_instance_t *parse_stage_instance(JSON_Value *stage_instance_value) {
    JSON_Object *stage_instance = json_object(stage_instance_value);
    stage_instance_t *result = yadl_malloc(sizeof(stage_instance_t));

    *result = (stage_instance_t) {(char *) json_object_get_string(stage_instance, "id"),
                                  (char *) json_object_get_string(stage_instance, "guild_id"),
                                  (char *) json_object_get_string(stage_instance, "channel_id"),
                                  (char *) json_object_get_string(stage_instance, "topic"),
                                  (int) json_object_get_number(stage_instance, "privacy_level"),
                                  yadl_json_boolean_null_check(json_object_get_boolean(stage_instance, "discoverable_disabled"))
    };

    return result;
}

JSON_Value *struct_stage_instance(stage_instance_t *stage_instance) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    json_object_set_string(result, "id", stage_instance->id);
    json_object_set_string(result, "guild_id", stage_instance->guild_id);
    json_object_set_string(result, "channel_id", stage_instance->channel_id);
    json_object_set_string(result, "topic", stage_instance->topic);
    json_object_set_number(result, "privacy_level", stage_instance->privacy_level);
    json_object_set_boolean(result, "discoverable_disabled", stage_instance->discoverable_disabled);

    return json_object_get_wrapping_value(result);
}
JSON_Value *struct_invite_stage_instance(invite_stage_instance_t *invite_stage_instance) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    json_object_set_string(result, "members", invite_stage_instance->members);
    json_object_set_number(result, "participant_count", invite_stage_instance->participant_count);
    json_object_set_number(result, "speaker_count", invite_stage_instance->speaker_count);
    json_object_set_string(result, "topic", invite_stage_instance->topic);

    return json_object_get_wrapping_value(result);
}
JSON_Value *struct_invite_metadata(invite_metadata_t *invite_metadata) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    json_object_set_number(result, "uses", invite_metadata->uses);
    json_object_set_number(result, "max_uses", invite_metadata->max_uses);
    json_object_set_number(result, "max_age", invite_metadata->max_age);
    json_object_set_boolean(result, "temporary", invite_metadata->temporary);
    json_object_set_string(result, "created_at", invite_metadata->created_at);

    return json_object_get_wrapping_value(result);
}
JSON_Value *struct_invite(invite_t *invite) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    json_object_set_string(result, "code", invite->code);
    json_object_set_value(result, "guild", struct_guild(invite->guild));
    json_object_set_value(result, "channel", struct_channel(invite->channel));
    json_object_set_value(result, "inviter", struct_user(invite->inviter));
    json_object_set_number(result, "target_type", invite->target_type);
    json_object_set_value(result, "target_user", struct_user(invite->target_user));
    json_object_set_value(result, "target_application", struct_application(invite->target_application));
    json_object_set_number(result, "approximate_presence_count", invite->approximate_presence_count);
    json_object_set_number(result, "approximate_member_count", invite->approximate_member_count);
    json_object_set_string(result, "expires_at", invite->expires_at);
    json_object_set_value(result, "stage_instance", struct_invite_stage_instance(invite->stage_instance));
    json_object_set_value(result, "guild_scheduled_event", struct_guild_scheduled_event(invite->guild_scheduled_event));

    return json_object_get_wrapping_value(result);
}
