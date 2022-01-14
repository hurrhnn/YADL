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

#include "impl.h"
#include "../yadl.h"

void yadl_object_init(yadl_context_t *context) {
    context->guilds = put_list(YADL_OBJECT_GUILD, NULL, "", NULL);
    context->users = put_list(YADL_OBJECT_USER, NULL, "", NULL);

    context->dm_channels = put_list(YADL_OBJECT_CHANNEL, NULL, "", NULL);

    context->guild_text_channels = put_list(YADL_OBJECT_CHANNEL, NULL, "", NULL);
    context->guild_voice_channels = put_list(YADL_OBJECT_CHANNEL, NULL, "", NULL);
}

bool yadl_object_overridable(size_t type) {
    switch (type) {
        case YADL_OBJECT_USER:
            return true;
        default:
            return false;
    }
}

void *yadl_object_override(obj_list_t *list, char* key, void* object, yadl_object_metadata_t *metadata) {
    size_t struct_size = 0, current_size = 0, idx = 0;
    for(int i = 0; i < strlen(metadata->member_size); i++)
        struct_size += metadata->member_size[i] - '0';

    void *exist_object = get_list(list, key), *new_object = yadl_malloc(struct_size, true);
    while(true) {
        if(struct_size == current_size)
            break;
        size_t member_size = metadata->member_size[idx++] - '0';
        int64_t exist_data, override_data;

        memset(&exist_data, 0x0, sizeof(int64_t));
        memset(&override_data, 0x0, sizeof(int64_t));

        memcpy(&exist_data, exist_object + current_size, member_size);
        memcpy(&override_data, object + current_size, member_size);
        current_size += member_size;

        if(exist_data == 0x0 || exist_data != override_data)
            exist_data = override_data;

        memcpy(new_object, exist_object + current_size, member_size);
    }

    return new_object;
}

yadl_object_array_t *yadl_object_array_parse(size_t type, JSON_Array *json_array) {
    yadl_object_array_t *result = yadl_malloc(sizeof(yadl_object_array_t));
    result->size = json_array_get_count(json_array);
    result->array = yadl_malloc(result->size * sizeof(void *));

    switch (type) {
        case YADL_OBJECT_APPLICATION:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_application(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_AUDIT_LOG:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_audit_log(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_AUDIT_LOG_ENTRY:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_audit_log_entry(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_AUDIT_LOG_CHANGE:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_audit_log_change(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_CHANNEL:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_channel(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_MESSAGE:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_message(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_MESSAGE_ACTIVITY:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_message_activity(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_MESSAGE_REFERENCE:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_message_reference(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_FOLLOWED_CHANNEL:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_followed_channel(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_REACTION:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_reaction(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_OVERWRITE:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_overwrite(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_THREAD_METADATA:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_thread_metadata(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_THREAD_MEMBER:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_thread_member(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_EMBED:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_embed(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_EMBED_THUMBNAIL:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_embed_thumbnail(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_EMBED_VIDEO:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_embed_video(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_EMBED_IMAGE:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_embed_image(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_EMBED_PROVIDER:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_embed_provider(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_EMBED_AUTHOR:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_embed_author(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_EMBED_FOOTER:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_embed_footer(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_EMBED_FIELD:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_embed_field(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_ATTACHMENT:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_attachment(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_CHANNEL_MENTION:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_channel_mention(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_ALLOWED_MENTIONS:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_allowed_mentions(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_EMOJI:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_emoji(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_GUILD:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_guild(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_GUILD_PREVIEW:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_guild_preview(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_GUILD_WIDGET:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_guild_widget(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_GUILD_MEMBER:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_guild_member(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_INTEGRATION:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_integration(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_INTEGRATION_ACCOUNT:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_integration_account(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_INTEGRATION_APPLICATION:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_integration_application(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_BAN:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_ban(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_WELCOME_SCREEN:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_welcome_screen(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_WELCOME_SCREEN_CHANNEL:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_welcome_screen_channel(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_GUILD_SCHEDULED_EVENT:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_guild_scheduled_event(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_GUILD_SCHEDULED_EVENT_USER:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_guild_scheduled_event_user(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_GUILD_TEMPLATE:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_guild_template(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_INVITE:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_invite(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_INVITE_METADATA:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_invite_metadata(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_INVITE_STAGE_INSTANCE:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_invite_stage_instance(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_STAGE_INSTANCE:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_stage_instance(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_STICKER:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_sticker(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_STICKER_ITEM:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_sticker_item(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_STICKER_PACK:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_sticker_pack(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_USER:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_user(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_VOICE_STATE:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_voice_state(json_array_get_value(json_array, i));
            break;


        case YADL_OBJECT_VOICE_REGION:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_voice_region(json_array_get_value(json_array, i));
            break;


        case YADL_OBJECT_WEBHOOK:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_webhook(json_array_get_value(json_array, i));
            break;


        case YADL_OBJECT_TEAM:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_team(json_array_get_value(json_array, i));
            break;

        case YADL_OBJECT_TEAM_MEMBER:
            for(int i = 0; i < result->size; i++)
                result->array[i] = parse_team_member(json_array_get_value(json_array, i));
            break;

        default:
            break;
    }

    return result;
}
