cmake_minimum_required(VERSION 3.1)
project(YADL C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS_RELEASE "-O3")

find_package(OpenSSL REQUIRED)
add_library(_libwebsockets STATIC IMPORTED)
add_library(_libsodium STATIC IMPORTED)
add_library(_libopus STATIC IMPORTED)
add_library(_parson STATIC IMPORTED)

configure_file(CMakeLists.txt.in.libwebsockets ${CMAKE_CURRENT_SOURCE_DIR}/submodules/libwebsockets/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" . WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/submodules/libwebsockets)
execute_process(COMMAND ${CMAKE_COMMAND} --build . WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/submodules/libwebsockets)

configure_file(CMakeLists.txt.in.libsodium ${CMAKE_CURRENT_SOURCE_DIR}/submodules/libsodium/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" . WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/submodules/libsodium)
execute_process(COMMAND ${CMAKE_COMMAND} --build . WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/submodules/libsodium)

configure_file(CMakeLists.txt.in.libopus ${CMAKE_CURRENT_SOURCE_DIR}/submodules/libopus/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" . WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/submodules/libopus)
execute_process(COMMAND ${CMAKE_COMMAND} --build . WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/submodules/libopus)

configure_file(CMakeLists.txt.in.parson ${CMAKE_CURRENT_SOURCE_DIR}/submodules/parson/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" . WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/submodules/parson)
execute_process(COMMAND ${CMAKE_COMMAND} --build . WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/submodules/parson)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/submodules/libsodium/src/libsodium-build/libsodium.a ${CMAKE_CURRENT_BINARY_DIR}/install/lib/libsodium.a COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/submodules/libsodium/src/libsodium/libsodium/src/libsodium/include/sodium.h ${CMAKE_CURRENT_BINARY_DIR}/install/include/sodium.h COPYONLY)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/submodules/libsodium/src/libsodium/libsodium/src/libsodium/include/sodium/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/install/include/sodium)

if(WIN32)
    set(prefix "")
    set(suffix ".lib")
else()
    set(prefix "lib")
    set(suffix ".a")
endif()

find_library(LIBWEBSOCKETS_STATIC_LIBRARIES NAMES "${prefix}websockets${suffix}" HINTS ${CMAKE_CURRENT_BINARY_DIR}/install/lib ${CMAKE_CURRENT_BINARY_DIR}/install/lib64)
find_library(LIBSODIUM_STATIC_LIBRARIES NAMES "${prefix}sodium${suffix}" HINTS ${CMAKE_CURRENT_BINARY_DIR}/install/lib ${CMAKE_CURRENT_BINARY_DIR}/install/lib64)
find_library(LIBOPUS_STATIC_LIBRARIES NAMES "${prefix}opus${suffix}" HINTS ${CMAKE_CURRENT_BINARY_DIR}/install/lib ${CMAKE_CURRENT_BINARY_DIR}/install/lib64)
find_library(PARSON_STATIC_LIBRARIES NAMES "${prefix}parson${suffix}" HINTS ${CMAKE_CURRENT_BINARY_DIR}/install/lib ${CMAKE_CURRENT_BINARY_DIR}/install/lib64)

set_target_properties(_libwebsockets PROPERTIES IMPORTED_LOCATION ${LIBWEBSOCKETS_STATIC_LIBRARIES})
set_target_properties(_libsodium PROPERTIES IMPORTED_LOCATION ${LIBSODIUM_STATIC_LIBRARIES})
set_target_properties(_libopus PROPERTIES IMPORTED_LOCATION ${LIBOPUS_STATIC_LIBRARIES})
set_target_properties(_parson PROPERTIES IMPORTED_LOCATION ${PARSON_STATIC_LIBRARIES})

add_library(YADL STATIC src/http/http_request.c src/http/http_request.h src/http/http_payload.h src/yadl.h src/http/http_result.h src/utils/utils.c src/utils/utils.h src/websockets/main_client.c src/websockets/main_client.h src/gc/gc.h src/gc/gc.c src/gc/binary_tree.c src/gc/binary_tree.h src/json/json.c src/json/json.h src/gc/pthread.c src/gc/pthread.h src/impl/user.c src/impl/user.h src/yadl.c src/yadl.h src/api/create_message.c src/api/create_message.h src/callback/callback.c src/callback/callback.h src/impl/guild.c src/impl/guild.h src/impl/linked_list.c src/impl/linked_list.h src/impl/impl.c src/impl/impl.h src/impl/application.c src/impl/application.h src/impl/channel.c src/impl/channel.h src/impl/message.c src/impl/message.h src/impl/embed.c src/impl/embed.h src/impl/audit_log.c src/impl/audit_log.h src/impl/attachment.c src/impl/attachment.h src/impl/reaction.c src/impl/reaction.h src/impl/thread.c src/impl/thread.h src/impl/integration.c src/impl/integration.h src/impl/emoji.c src/impl/emoji.h src/impl/sticker.c src/impl/sticker.h src/impl/invite.c src/impl/invite.h src/impl/voice.c src/impl/voice.h src/impl/webhook.c src/impl/webhook.h src/api/api.c src/api/api.h src/utils/info.h src/api/retrieve_self_user.c src/api/retrieve_self_user.h src/api/retrieve_self_user.c src/api/retrieve_self_user.h src/api/retrieve_user_by_id.c src/api/retrieve_user_by_id.h src/api/retrieve_application_info.c src/api/retrieve_application_info.h src/impl/impl-inl.h src/api/retrieve_channel_by_id.c src/api/retrieve_channel_by_id.h src/websockets/voice_client.c src/websockets/voice_client.h src/raw/voice_udp_client.c src/raw/voice_udp_client.h)
add_dependencies(YADL _libwebsockets _libsodium _libopus _parson)
target_include_directories(YADL PUBLIC ${OPENSSL_INCLUDE_DIR})
target_include_directories(YADL PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/install/include)
target_link_libraries(YADL m z dl pthread _libwebsockets _libsodium _libopus _parson ${OPENSSL_LIBRARIES})

add_executable(test_yadl test.c)
add_dependencies(test_yadl YADL)
target_include_directories(test_yadl PUBLIC ${OPENSSL_INCLUDE_DIR})
target_include_directories(test_yadl PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/install/include)
target_link_libraries(test_yadl YADL)
