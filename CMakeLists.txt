cmake_minimum_required(VERSION 3.10)
project(YADL VERSION 0.0.7 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} -O2")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -g")

option(YADL_BUILD_DEPS "Try to build core dependencies." OFF)
option(YADL_DISABLE_TESTS "Disable building YADL library test code." OFF)
option(YADL_INSTALL_PKGCONFIG "install pkg-config module." ON)

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(LINUX ON)
else ()
    set(LINUX OFF)
endif ()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
find_package(OpenSSL REQUIRED)
find_package(Pthread REQUIRED)
find_package(LibUv REQUIRED)
find_package(LibDl REQUIRED)
find_package(LibM REQUIRED)
find_package(LibZ REQUIRED)

set(YADL_DEP_LIBRARIES "")
set(YADL_DEP_INCLUDES "")

if(LINUX)
    find_package(LibCap REQUIRED)
    list(APPEND YADL_DEP_LIBRARIES "cap")
endif()

list(APPEND YADL_DEP_LIBRARIES ${LIBZ_LIBRARIES})
list(APPEND YADL_DEP_INCLUDES ${LIBZ_INCLUDE_DIRS})

if(NOT APPLE)
    list(APPEND YADL_DEP_LIBRARIES ${LIBM_LIBRARIES})
    list(APPEND YADL_DEP_LIBRARIES ${LIBDL_LIBRARIES})
    list(APPEND YADL_DEP_LIBRARIES ${PTHREAD_LIBRARIES})

    list(APPEND YADL_DEP_INCLUDES ${LIBM_INCLUDE_DIRS})
    list(APPEND YADL_DEP_INCLUDES ${LIBDL_INCLUDE_DIRS})
    list(APPEND YADL_DEP_INCLUDES ${PTHREAD_INCLUDE_DIRS})
endif()

if (CMAKE_BUILD_TYPE MATCHES Debug)
    if (CMAKE_C_COMPILER_ID MATCHES "(GNU|Clang)" OR
            CMAKE_CXX_COMPILER_ID MATCHES "(GNU|Clang)")
        include(CodeCoverage)
        APPEND_COVERAGE_COMPILER_FLAGS()
        setup_target_for_coverage_gcovr_sonarqube(NAME coverage EXECUTABLE ctest -j2 --output-on-failure --force-new-ctest-process --progress)
    endif ()
    set(YADL_ENABLE_DEBUG ON)
endif ()

configure_file(cmake/build_deps/CMakeLists.txt.in.parson ${CMAKE_CURRENT_SOURCE_DIR}/submodules/parson/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" . WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/submodules/parson)
execute_process(COMMAND ${CMAKE_COMMAND} --build . WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/submodules/parson)
find_library(PARSON_STATIC_LIBRARIES NAMES "${prefix}parson${suffix}" HINTS ${CMAKE_CURRENT_BINARY_DIR}/install/lib ${CMAKE_CURRENT_BINARY_DIR}/install/lib64)

configure_file(${PROJECT_SOURCE_DIR}/include/yadl/config.h.in ${PROJECT_SOURCE_DIR}/include/yadl/config.h)
FILE(GLOB_RECURSE YADL_PUBLIC_HEADER "include/*.h")
add_library(YADL SHARED include/yadl/config.h src/http/http_request.c include/yadl/http/http_request.h include/yadl/http/http_payload.h include/yadl.h include/yadl/http/http_result.h src/utils/utils.c include/yadl/utils/utils.h src/websockets/main_client.c include/yadl/websockets/main_client.h include/yadl/gc/gc.h src/gc/gc.c src/gc/binary_tree.c include/yadl/gc/binary_tree.h src/json/json.c include/yadl/json/json.h src/gc/pthread.c include/yadl/gc/pthread.h src/impl/user.c include/yadl/impl/user.h src/yadl.c include/yadl.h src/api/create_message.c include/yadl/api/create_message.h src/callback/callback.c include/yadl/callback/callback.h src/impl/guild.c include/yadl/impl/guild.h src/impl/linked_list.c include/yadl/impl/linked_list.h src/impl/impl.c include/yadl/impl/impl.h src/impl/application.c include/yadl/impl/application.h src/impl/channel.c include/yadl/impl/channel.h src/impl/message.c include/yadl/impl/message.h src/impl/embed.c include/yadl/impl/embed.h src/impl/audit_log.c include/yadl/impl/audit_log.h src/impl/attachment.c include/yadl/impl/attachment.h src/impl/reaction.c include/yadl/impl/reaction.h src/impl/thread.c include/yadl/impl/thread.h src/impl/integration.c include/yadl/impl/integration.h src/impl/emoji.c include/yadl/impl/emoji.h src/impl/sticker.c include/yadl/impl/sticker.h src/impl/invite.c include/yadl/impl/invite.h src/impl/voice.c include/yadl/impl/voice.h src/impl/webhook.c include/yadl/impl/webhook.h src/api/api.c include/yadl/api/api.h include/yadl/config.h src/api/retrieve_self_user.c include/yadl/api/retrieve_self_user.h src/api/retrieve_self_user.c include/yadl/api/retrieve_self_user.h src/api/retrieve_user_by_id.c include/yadl/api/retrieve_user_by_id.h src/api/retrieve_application_info.c include/yadl/api/retrieve_application_info.h src/impl/impl-inl.h src/api/retrieve_channel_by_id.c include/yadl/api/retrieve_channel_by_id.h src/websockets/voice_client.c include/yadl/websockets/voice_client.h src/raw/voice_udp_client.c include/yadl/raw/voice_udp_client.h)

if(YADL_BUILD_DEPS)
    configure_file(cmake/build_deps/CMakeLists.txt.in.libwebsockets ${CMAKE_CURRENT_SOURCE_DIR}/submodules/libwebsockets/CMakeLists.txt)
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" . WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/submodules/libwebsockets)
    execute_process(COMMAND ${CMAKE_COMMAND} --build . WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/submodules/libwebsockets)

    configure_file(cmake/build_deps/CMakeLists.txt.in.libsodium ${CMAKE_CURRENT_SOURCE_DIR}/submodules/libsodium/CMakeLists.txt)
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" . WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/submodules/libsodium)
    execute_process(COMMAND ${CMAKE_COMMAND} --build . WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/submodules/libsodium)

    configure_file(cmake/build_deps/CMakeLists.txt.in.libopus ${CMAKE_CURRENT_SOURCE_DIR}/submodules/libopus/CMakeLists.txt)
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" . WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/submodules/libopus)
    execute_process(COMMAND ${CMAKE_COMMAND} --build . WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/submodules/libopus)

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/submodules/libsodium/src/libsodium-build/libsodium.so ${CMAKE_CURRENT_BINARY_DIR}/install/lib/libsodium.so COPYONLY)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/submodules/libsodium/src/libsodium/libsodium/src/libsodium/include/sodium.h ${CMAKE_CURRENT_BINARY_DIR}/install/include/sodium.h COPYONLY)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/submodules/libsodium/src/libsodium/libsodium/src/libsodium/include/sodium/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/install/include/sodium)

    find_library(LIBWEBSOCKETS_SHARED_LIBRARIES NAMES "websockets" HINTS ${CMAKE_CURRENT_BINARY_DIR}/install/lib ${CMAKE_CURRENT_BINARY_DIR}/install/lib64)
    find_library(LIBSODIUM_SHARED_LIBRARIES NAMES "sodium" HINTS ${CMAKE_CURRENT_BINARY_DIR}/install/lib ${CMAKE_CURRENT_BINARY_DIR}/install/lib64)
    find_library(LIBOPUS_SHARED_LIBRARIES NAMES "opus" HINTS ${CMAKE_CURRENT_BINARY_DIR}/install/lib ${CMAKE_CURRENT_BINARY_DIR}/install/lib64)

    add_dependencies(YADL _libwebsockets _libsodium _libopus _parson)
    list(APPEND YADL_DEP_INCLUDES ${OPENSSL_INCLUDE_DIR})
    list(APPEND YADL_DEP_INCLUDES ${CMAKE_CURRENT_BINARY_DIR}/install/include)

    list(APPEND YADL_DEP_LIBRARIES ${LIBWEBSOCKETS_SHARED_LIBRARIES})
    list(APPEND YADL_DEP_LIBRARIES ${LIBSODIUM_SHARED_LIBRARIES})
    list(APPEND YADL_DEP_LIBRARIES ${LIBOPUS_SHARED_LIBRARIES})

else()
    find_package(libwebsockets REQUIRED)
    find_package(LibSodium REQUIRED)
    find_package(LibOpus REQUIRED)

    list(APPEND YADL_DEP_INCLUDES ${OPENSSL_INCLUDE_DIR})
    list(APPEND YADL_DEP_INCLUDES ${OPUS_INCLUDE_DIR})
    list(APPEND YADL_DEP_INCLUDES ${LIBSODIUM_INCLUDE_DIR})
    list(APPEND YADL_DEP_INCLUDES ${LIBWEBSOCKETS_INCLUDE_DIR})
    list(APPEND YADL_DEP_INCLUDES ${CMAKE_CURRENT_BINARY_DIR}/install/include)

    list(APPEND YADL_DEP_LIBRARIES ${LIBWEBSOCKETS_SHARED_LIBRARIES})
    list(APPEND YADL_DEP_LIBRARIES ${LIBSODIUM_SHARED_LIBRARIES})
    list(APPEND YADL_DEP_LIBRARIES ${OPENSSL_LIBRARIES})
    list(APPEND YADL_DEP_LIBRARIES ${OPUS_LIBRARIES})
    list(APPEND YADL_DEP_LIBRARIES ${LIBSODIUM_LIBRARIES})
    list(APPEND YADL_DEP_LIBRARIES ${LIBWEBSOCKETS_LIBRARIES})
endif()
list(APPEND YADL_DEP_LIBRARIES ${PARSON_STATIC_LIBRARIES})

target_link_libraries(YADL ${YADL_DEP_LIBRARIES})
if (LINUX)
    if (CMAKE_BUILD_TYPE MATCHES Debug AND
    (CMAKE_C_COMPILER_ID MATCHES "(GNU|Clang)" OR
    CMAKE_CXX_COMPILER_ID MATCHES "(GNU|Clang)"))
    target_link_libraries(bufep gcov)
    endif ()
endif ()

set_target_properties(YADL
        PROPERTIES SOVERSION
        ${PROJECT_VERSION_MAJOR}
        VERSION
        ${CMAKE_PROJECT_VERSION}
        PUBLIC_HEADER
        "${YADL_PUBLIC_HEADER}")

target_include_directories(
        YADL
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/yadl>
        ${YADL_DEP_INCLUDES})

install(TARGETS YADL
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/yadl)

if (YADL_INSTALL_PKGCONFIG)
    set(prefix ${CMAKE_INSTALL_PREFIX})
    set(exec_prefix ${CMAKE_INSTALL_PREFIX})
    set(libdir ${CMAKE_INSTALL_FULL_LIBDIR})
    set(includedir ${CMAKE_INSTALL_FULL_INCLUDEDIR})
    set(VERSION ${CMAKE_PROJECT_VERSION})

    configure_file(yadl.pc.in yadl.pc)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/yadl.pc
            DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}/pkgconfig)
endif ()

if (NOT TARGET uninstall)
    configure_file(
            "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
            "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake"
            IMMEDIATE @ONLY)

    add_custom_target(uninstall
            COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake)
endif ()

if (NOT YADL_DISABLE_TESTS)
    enable_testing()
    if (MSVC)
        add_custom_command(TARGET YADL
                POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:yadl> "${CMAKE_CURRENT_BINARY_DIR}/test/"
                COMMENT "Copy dll file to ${CMAKE_CURRENT_BINARY_DIR} directory" VERBATIM
        )
    endif ()
    add_subdirectory(test)
endif ()
