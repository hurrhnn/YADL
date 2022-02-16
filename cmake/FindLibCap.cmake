include(FindPackageHandleStandardArgs)
find_path(LIBCAP_INCLUDE_DIRS
        capability.h
        PATHS /usr/include/sys
        )

find_library(LIBCAP_LIBRARIES
        NAME cap
        PATH_SUFFIXES ${LIBRARY_PATH_PREFIX}
        )

find_package_handle_standard_args(LibCap DEFAULT_MSG
        LIBCAP_INCLUDE_DIRS LIBCAP_LIBRARIES)
