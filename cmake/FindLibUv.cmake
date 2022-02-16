find_library(LIBUV_LIBRARIES
        NAMES uv
        )
mark_as_advanced(LIBUV_LIBRARIES)

find_path(LIBUV_INCLUDE_DIR
        NAMES uv.h
        )
mark_as_advanced(LIBUV_INCLUDE_DIR)

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LibUv
        FOUND_VAR LIBUV_FOUND
        REQUIRED_VARS LIBUV_LIBRARIES LIBUV_INCLUDE_DIR
        )
set(LIBUV_FOUND ${LIBUV_FOUND})

if(LIBUV_FOUND)
    set(LIBUV_INCLUDE_DIRS ${LIBUV_INCLUDE_DIR})
    set(LIBUV_LIBRARIES ${LIBUV_LIBRARIES})
    if(NOT TARGET LIBUV::LIBUV)
        add_library(LIBUV::LIBUV UNKNOWN IMPORTED)
        set_target_properties(LIBUV::LIBUV PROPERTIES
                IMPORTED_LOCATION "${LIBUV_LIBRARIES}"
                INTERFACE_INCLUDE_DIRECTORIES "${LIBUV_INCLUDE_DIRS}"
                )
    endif()
endif()
