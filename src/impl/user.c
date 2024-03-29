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

#include <yadl/impl/user.h>

user_t *parse_user(JSON_Value *user_value) {
    JSON_Object *user = json_object(user_value);
    user_t *result = yadl_malloc(sizeof(user_t));

    *result = (user_t) {(char *) json_object_get_string(user, "id"),
                        (char *) json_object_get_string(user, "username"),
                        (char *) json_object_get_string(user, "discriminator"),
                        (char *) json_object_get_string(user, "avatar"),
                        yadl_json_boolean_null_check(json_object_get_boolean(user, "bot")),
                        yadl_json_boolean_null_check(json_object_get_boolean(user, "system")),
                        yadl_json_boolean_null_check(json_object_get_boolean(user, "mfa_enabled")),
                        (char *) json_object_get_string(user, "banner"),
                        (int) json_object_get_number(user, "accent_color"),
                        (char *) json_object_get_string(user, "locale"),
                        yadl_json_boolean_null_check(json_object_get_boolean(user, "verified")),
                        (char *) json_object_get_string(user, "email"),
                        (int) json_object_get_number(user, "flags"),
                        (int) json_object_get_number(user, "premium_type"),
                        (int) json_object_get_number(user, "public_flags")
    };

    char *avatar = yadl_malloc(YADL_MIDIUM_SIZE);
    sprintf(avatar, yadl_strcat(YADL_CDN_URL, YADL_USER_AVATAR), result->id, result->avatar);
    result->avatar = avatar;

    return result;
}

JSON_Value *struct_user(user_t *user) {
    JSON_Object *result = yadl_json_object_builder(NULL);

    json_object_set_string(result, "id", user->id);
    json_object_set_string(result, "username", user->username);
    json_object_set_string(result, "discriminator", user->discriminator);
    json_object_set_string(result, "avatar", user->avatar);
    json_object_set_boolean(result, "bot", user->bot);
    json_object_set_boolean(result, "system", user->system);
    json_object_set_boolean(result, "mfa_enabled", user->mfa_enabled);
    json_object_set_string(result, "banner", user->banner);
    json_object_set_number(result, "accent_color", user->accent_color);
    json_object_set_string(result, "locale", user->locale);
    json_object_set_boolean(result, "verified", user->verified);
    json_object_set_string(result, "email", user->email);
    json_object_set_number(result, "flags", user->flags);
    json_object_set_number(result, "premium_type", user->premium_type);
    json_object_set_number(result, "public_flags", user->public_flags);

    return json_object_get_wrapping_value(result);
}
