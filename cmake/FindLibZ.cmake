include(FindPackageHandleStandardArgs)

if (LIBZ_INCLUDE_DIRS AND LIBZ_LIBRARY)
    set(LIBZ_FIND_QUIETLY TRUE)
else ()
    find_path(
            LIBZ_INCLUDE_DIR
            NAMES zlib.h
            HINTS ${LIBZ_ROOT_DIR}
            PATH_SUFFIXES include)

    find_library(
            LIBZ_LIBRARIES
            NAMES z
            HINTS ${LIBZ_ROOT_DIR}
            PATH_SUFFIXES ${LIBRARY_PATH_PREFIX})

    set(LIBZ_INCLUDE_DIRS ${LIBZ_INCLUDE_DIR})

    find_package_handle_standard_args(
            LibZ
            DEFAULT_MSG
            LIBZ_LIBRARIES LIBZ_INCLUDE_DIRS)

    mark_as_advanced(LIBZ_LIBRARIES LIBZ_INCLUDE_DIRS)
endif ()
