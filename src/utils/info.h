#ifndef YADL_INFO_H
#define YADL_INFO_H

#define YADL_MAJOR_VERSION "0"
#define YADL_MINOR_VERSION "0"
#define YADL_REVISION "3"
#define YADL_VERSION (YADL_MAJOR_VERSION "." YADL_MINOR_VERSION "." YADL_REVISION)

#define YADL_DEFAULT_API_VER 9
#define YADL_DEFAULT_GATEWAY_VER 9
#define YADL_DEFAULT_VOICE_VER 4

#define YADL_APPLICATION "YADL"
#define YADL_USER_AGENT "Mozilla/5.0 (X11; Fedora; Linux x86_64; rv:91.0) Gecko/20100101 Firefox/91.0"
#define YADL_AUTHORIZATION_HEADER "Authorization: Bot %s"

#define YADL_RETRIEVE_GATEWAY_URL "https://discord.com/api/gateway"

#define YADL_GATEWAY_PATH "/?v=%d&encoding=json"
#define YADL_VOICE_PATH "/?v=%d"
#define YADL_CREATE_MESSAGE_PATH "/channels/%s/messages"

#define YADL_API_URL "https://discord.com/api/v%d"
#define YADL_CDN_URL "https://cdn.discordapp.com"

#endif //YADL_INFO_H
