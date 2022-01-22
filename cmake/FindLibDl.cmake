include(CheckFunctionExists)

find_path(LIBDL_INCLUDE_DIR NAMES dlfcn.h)
find_library(LIBDL_LIBRARIES NAMES dl)
if (LIBDL_LIBRARIES)
    set(LIBDL_FOUND TRUE)
else (LIBDL_LIBRARIES)
    check_function_exists(dlopen LIBDL_FOUND)
    # If dlopen can be found without linking in dl then dlopen is part
    # of libc, so don't need to link extra libs.
    set(LIBDL_LIBRARIES "")
endif (LIBDL_LIBRARIES)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LibDl
        FOUND_VAR
        LIBDL_FOUND
        REQUIRED_VARS
        LIBDL_INCLUDE_DIR
        )

mark_as_advanced(LIBDL_INCLUDE_DIR LIBDL_LIBRARIES)

if (LIBDL_FOUND AND NOT TARGET DL::DL)
    if (LIBDL_LIBRARIES)
        add_library(DL::DL UNKNOWN IMPORTED)
        set_target_properties(DL::DL PROPERTIES
                IMPORTED_LOCATION "${LIBDL_LIBRARIES}")
    else ()
        add_library(DL::DL INTERFACE IMPORTED)
    endif ()
    set_target_properties(DL::DL PROPERTIES
            INTERFACE_INCLUDE_DIRECTORIES "${LIBDL_INCLUDE_DIR}"
            )
endif ()