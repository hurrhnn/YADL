cmake_minimum_required(VERSION 3.1)
project(YADL C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS_RELEASE "-O3")

find_package(OpenSSL REQUIRED)
add_library(_libwebsockets STATIC IMPORTED)
add_library(_parson STATIC IMPORTED)

configure_file(CMakeLists.txt.in.libwebsockets ${CMAKE_CURRENT_SOURCE_DIR}/submodules/libwebsockets/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" . WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/submodules/libwebsockets)
execute_process(COMMAND ${CMAKE_COMMAND} --build . WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/submodules/libwebsockets)

configure_file(CMakeLists.txt.in.parson ${CMAKE_CURRENT_SOURCE_DIR}/submodules/parson/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" . WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/submodules/parson)
execute_process(COMMAND ${CMAKE_COMMAND} --build . WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/submodules/parson)

if(WIN32)
    set(prefix "")
    set(suffix ".lib")
else()
    set(prefix "lib")
    set(suffix ".a")
endif()

find_library(LIBWEBSOCKETS_STATIC_LIBRARIES NAMES "${prefix}websockets${suffix}" HINTS ${CMAKE_CURRENT_BINARY_DIR}/install/lib ${CMAKE_CURRENT_BINARY_DIR}/install/lib64)
find_library(LIBSIGSEGV_STATIC_LIBRARIES NAMES "${prefix}parson${suffix}" HINTS ${CMAKE_CURRENT_BINARY_DIR}/install/lib ${CMAKE_CURRENT_BINARY_DIR}/install/lib64)

set_target_properties(_libwebsockets PROPERTIES IMPORTED_LOCATION ${LIBWEBSOCKETS_STATIC_LIBRARIES})
set_target_properties(_parson PROPERTIES IMPORTED_LOCATION ${LIBSIGSEGV_STATIC_LIBRARIES})

add_library(YADL STATIC src/utils/http/http_request.c src/utils/http/http_request.h src/utils/http/http_payload.h src/yadl.h src/utils/http/http_result.h src/utils/utils.c src/utils/utils.h src/utils/websockets/main_client.c src/utils/websockets/main_client.h src/utils/gc/gc.h src/utils/gc/gc.c src/utils/gc/node_tree.c src/utils/gc/node_tree.h src/utils/json/json.c src/utils/json/json.h src/utils/gc/pthread.c src/utils/gc/pthread.h src/impl/user.c src/impl/user.h src/yadl.c src/yadl.h src/api/create_message.c src/api/create_message.h)
add_dependencies(YADL _libwebsockets _parson)
target_include_directories(YADL PUBLIC ${OPENSSL_INCLUDE_DIR})
target_include_directories(YADL PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/install/include)
target_link_libraries(YADL m dl pthread _libwebsockets _parson ${OPENSSL_LIBRARIES})

add_executable(test_yadl test.c)
add_dependencies(test_yadl _libwebsockets _parson)
target_link_libraries(test_yadl YADL)
target_include_directories(test_yadl PUBLIC ${OPENSSL_INCLUDE_DIR})
target_include_directories(test_yadl PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/install/include)
target_link_libraries(test_yadl YADL m dl pthread _libwebsockets _parson ${OPENSSL_LIBRARIES})
