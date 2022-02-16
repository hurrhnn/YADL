cmake_minimum_required(VERSION 3.10)
project(YADL VERSION 0.0.7)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")

option(YADL_BUILD_DEPS "Try to build core dependencies." OFF)
option(YADL_BUILD_TEST "Build YADL test code." OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
find_package(OpenSSL REQUIRED)
find_package(Pthread REQUIRED)
find_package(LibUv REQUIRED)
find_package(LibDl REQUIRED)
find_package(LibM REQUIRED)
find_package(LibZ REQUIRED)

set(OS_LIB_DEPS "")
set(OS_INC_DEPS "")

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    find_package(LibCap REQUIRED)
    list(APPEND OS_LIB_DEPS "cap")
endif()

if(NOT APPLE)
    list(APPEND OS_INC_DEPS ${LIBM_LIBRARIES})
    list(APPEND OS_INC_DEPS ${LIBZ_LIBRARIES})
    list(APPEND OS_INC_DEPS ${LIBDL_LIBRARIES})
    list(APPEND OS_INC_DEPS ${PTHREAD_LIBRARIES})
endif()

add_library(_parson STATIC IMPORTED)
configure_file(cmake/build_deps/CMakeLists.txt.in.parson ${CMAKE_CURRENT_SOURCE_DIR}/submodules/parson/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" . WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/submodules/parson)
execute_process(COMMAND ${CMAKE_COMMAND} --build . WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/submodules/parson)
find_library(PARSON_STATIC_LIBRARIES NAMES "${prefix}parson${suffix}" HINTS ${CMAKE_CURRENT_BINARY_DIR}/install/lib ${CMAKE_CURRENT_BINARY_DIR}/install/lib64)
set_target_properties(_parson PROPERTIES IMPORTED_LOCATION ${PARSON_STATIC_LIBRARIES})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/yadl/yadl-config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/include/yadl/yadl-config.h)
add_library(YADL SHARED src/http/http.c include/yadl/yadl-http.h include/yadl.h src/utils/utils.c include/yadl/yadl-utils.h src/websockets/main_client.c src/websockets/main_client.h include/yadl/yadl-gc.h src/gc/gc.c src/gc/gc_tree.c include/yadl/gc/gc_tree.h src/json/json.c include/yadl/yadl-json.h src/gc/pthread.c include/yadl/gc/pthread.h src/impl/user.c src/impl/user.h src/yadl.c include/yadl.h src/api/create_message.c include/yadl/api/create_message.h src/callback/callback.c include/yadl/yadl-callback.h src/impl/guild.c src/impl/guild.h src/impl/linked_list.c src/impl/linked_list.h src/impl/impl.c src/impl/impl.h src/impl/application.c src/impl/application.h src/impl/channel.c src/impl/channel.h src/impl/message.c src/impl/message.h src/impl/embed.c src/impl/embed.h src/impl/audit_log.c src/impl/audit_log.h src/impl/attachment.c src/impl/attachment.h src/impl/reaction.c src/impl/reaction.h src/impl/thread.c src/impl/thread.h src/impl/integration.c src/impl/integration.h src/impl/emoji.c src/impl/emoji.h src/impl/sticker.c src/impl/sticker.h src/impl/invite.c src/impl/invite.h src/impl/voice.c src/impl/voice.h src/impl/webhook.c src/impl/webhook.h include/yadl/yadl-api.h src/api/retrieve_self_user.c include/yadl/api/retrieve_self_user.h src/api/retrieve_self_user.c include/yadl/api/retrieve_self_user.h src/api/retrieve_user_by_id.c include/yadl/api/retrieve_user_by_id.h src/api/retrieve_application_info.c include/yadl/api/retrieve_application_info.h src/impl/impl-inl.h src/api/retrieve_channel_by_id.c include/yadl/api/retrieve_channel_by_id.h src/websockets/voice_client.c src/websockets/voice_client.h src/raw/voice_udp_client.c src/raw/voice_udp_client.h)

if(YADL_BUILD_DEPS)
    add_library(_libwebsockets STATIC IMPORTED)
    add_library(_libsodium STATIC IMPORTED)
    add_library(_libopus STATIC IMPORTED)

    configure_file(cmake/build_deps/CMakeLists.txt.in.libwebsockets ${CMAKE_CURRENT_SOURCE_DIR}/submodules/libwebsockets/CMakeLists.txt)
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" . WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/submodules/libwebsockets)
    execute_process(COMMAND ${CMAKE_COMMAND} --build . WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/submodules/libwebsockets)

    configure_file(cmake/build_deps/CMakeLists.txt.in.libsodium ${CMAKE_CURRENT_SOURCE_DIR}/submodules/libsodium/CMakeLists.txt)
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" . WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/submodules/libsodium)
    execute_process(COMMAND ${CMAKE_COMMAND} --build . WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/submodules/libsodium)

    configure_file(cmake/build_deps/CMakeLists.txt.in.libopus ${CMAKE_CURRENT_SOURCE_DIR}/submodules/libopus/CMakeLists.txt)
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" . WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/submodules/libopus)
    execute_process(COMMAND ${CMAKE_COMMAND} --build . WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/submodules/libopus)

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

    set_target_properties(_libwebsockets PROPERTIES IMPORTED_LOCATION ${LIBWEBSOCKETS_STATIC_LIBRARIES})
    set_target_properties(_libsodium PROPERTIES IMPORTED_LOCATION ${LIBSODIUM_STATIC_LIBRARIES})
    set_target_properties(_libopus PROPERTIES IMPORTED_LOCATION ${LIBOPUS_STATIC_LIBRARIES})

    add_dependencies(YADL _libwebsockets _libsodium _libopus _parson)
    target_include_directories(YADL PUBLIC ${CMAKE_SOURCE_DIR}/include ${OS_INC_DEPS} ${OPENSSL_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/install/include)
    target_link_libraries(YADL _libwebsockets _libsodium _libopus _parson ${OS_LIB_DEPS} ${LIBM_LIBRARIES} ${LIBZ_LIBRARIES} ${LIBDL_LIBRARIES} ${PTHREAD_LIBRARIES} ${OPENSSL_LIBRARIES})
else()
    find_package(libwebsockets REQUIRED)
    find_package(LibSodium REQUIRED)
    find_package(LibOpus REQUIRED)

    add_dependencies(YADL _parson)
    target_include_directories(YADL PUBLIC ${CMAKE_SOURCE_DIR}/include ${OS_INC_DEPS} ${OPENSSL_INCLUDE_DIR} ${OPUS_INCLUDE_DIR} ${LIBSODIUM_INCLUDE_DIR} ${LIBWEBSOCKETS_INCLUDE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/install/include)
    target_link_libraries(YADL _parson ${OS_LIB_DEPS} ${LIBM_LIBRARIES} ${LIBZ_LIBRARIES} ${LIBDL_LIBRARIES} ${PTHREAD_LIBRARIES} ${OPENSSL_LIBRARIES} ${OPUS_LIBRARIES} ${LIBSODIUM_LIBRARIES} ${LIBWEBSOCKETS_LIBRARIES})
endif()

if(YADL_BUILD_TEST)
    add_executable(test_yadl test.c)
    add_dependencies(test_yadl YADL)
    target_link_libraries(test_yadl YADL)
endif()
