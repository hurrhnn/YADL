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

#include "yadl.h"

void yadl_init(yadl_context_t *context) {
    if (sodium_init() < 0) {
        lwsl_err("[global] Panic! the sodium library couldn't be initialized. exit.");
        exit(EXIT_FAILURE);
    }
    yadl_context_info_t *yadl_info = &context->info;

    YADL_SET_VALUE_IF_NULL(yadl_info->API_VER, YADL_DEFAULT_API_VER);
    YADL_SET_VALUE_IF_NULL(yadl_info->GATEWAY_VER, YADL_DEFAULT_GATEWAY_VER);
    YADL_SET_VALUE_IF_NULL(yadl_info->VOICE_VER, YADL_DEFAULT_VOICE_VER);
    YADL_SET_VALUE_IF_NULL(yadl_info->GATEWAY_INTENTS, YADL_GATEWAY_INTENTS_DEFAULT);

    sprintf(yadl_info->AUTHORIZATION_HEADER, YADL_AUTHORIZATION_HEADER, yadl_info->TOKEN);
    sprintf(yadl_info->API_URL, YADL_API_URL, yadl_info->API_VER);
    sprintf(yadl_info->GATEWAY_PATH, YADL_GATEWAY_PATH, yadl_info->GATEWAY_VER);
    sprintf(yadl_info->VOICE_PATH, YADL_VOICE_PATH, yadl_info->VOICE_VER);
    sprintf(yadl_info->USER_AGENT, YADL_USER_AGENT);
    sprintf(yadl_info->APPLICATION, "%s v%s", YADL_APPLICATION, YADL_VERSION);

    yadl_gc_init();
    yadl_object_init(context);
}

void yadl_launch(yadl_context_t *context) {
    lws_set_log_level(LLL_ERR | LLL_WARN | LLL_USER | LLL_HEADER, NULL);
    start_main_client(context);
}

void yadl_cleanup(yadl_context_t *context) {
    free_node(yadl_gc_get_context(YADL_GC_NODE_ADDRESS));
    free_node(yadl_gc_get_context((int8_t) YADL_NON_GC_NODE));

    free_list(context->guilds);
    free_list(context->users);

    free_list(context->dm_channels);
    free_list(context->guild_text_channels);
    free_list(context->guild_voice_channels);
    yadl_free(context->self_user);
}
