find_path(LIBCAP_INCLUDE_DIRS
        capability.h
        PATHS /usr/include/sys
        NO_DEFAULT_PATH)

find_library(LIBCAP_LIBRARIES
        NAME cap
        PATHS /usr/lib64
        NO_DEFAULT_PATH)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LibCap DEFAULT_MSG
        LIBCAP_INCLUDE_DIRS LIBCAP_LIBRARIES)
