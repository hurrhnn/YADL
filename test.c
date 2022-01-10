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

#include <stdio.h>
#include "src/yadl.h"

void on_ready(const struct yadl_event_on_ready *event, void* user_data) {
    printf("YADL v%s Library Test Started.\n\n", YADL_VERSION);

    puts("===== On Ready =====");
    printf("Gateway Version: %d\n", event->gateway_version);
    printf("ID: %s\n", event->self_user->id);
    printf("Name: %s#%s\n", event->self_user->username, event->self_user->discriminator);
    printf("Guild Count: %d\n", event->unavailable_guild_count);
    puts("");
}

void on_guild_create(const struct yadl_event_on_guild_create *event, void *user_data) {
    printf("Guild Created: %s\n", event->guild->name);
}

int main(__attribute__((unused)) int argc, char **argv) {
    yadl_context_t yadl_context;
    memset(&yadl_context, 0x0, sizeof(yadl_context_t));

    const char *token_env = getenv("TOKEN"); // get token from environment variable.
    if (token_env == NULL) {
        lwsl_err("Token not provided. please run `TOKEN=<token> %s`.", argv[0]);
        exit(EXIT_FAILURE);
    }
    memcpy(yadl_context.info.TOKEN, token_env, strlen(token_env));

    yadl_gateway_intents gateway_intents = { .value = YADL_GATEWAY_INTENTS_ALL };
    gateway_intents.flags.GUILD_MEMBERS = false;
    gateway_intents.flags.GUILD_PRESENCES = false;

    yadl_context.info.GATEWAY_INTENTS = gateway_intents.value;
    yadl_context.callbacks.on_ready = on_ready;
    yadl_context.callbacks.on_guild_create = on_guild_create;
    yadl_context.callbacks.user_data = NULL;

    yadl_init(&yadl_context);
    yadl_launch(&yadl_context);
    yadl_cleanup();
    return 0;
}
