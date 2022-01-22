find_path(LIBM_INCLUDE_DIR math.h
        PATHS /usr/local/include /usr/include ${CMAKE_EXTRA_INCLUDES}
        )

find_library(LIBM_LIBRARIES m
        PATHS /usr/local/lib /usr/lib /lib ${CMAKE_EXTRA_LIBRARIES}
        )

if (LIBM_INCLUDE_DIR AND LIBM_LIBRARIES)
    set(HAVE_LIBM TRUE)
else (LIBM_INCLUDE_DIR AND LIBM_LIBRARIES)
    if (NOT LIBM_FIND_QUIETLY)
        if (NOT LIBM_INCLUDE_DIR)
            message(STATUS "Unable to find M header files!")
        endif (NOT LIBM_LIBRARIES)
        if (NOT LIBM_LIBRARIES)
            message(STATUS "Unable to find M library files!")
        endif (NOT LIBM_LIBRARIES)
    endif (NOT LIBM_FIND_QUIETLY)
endif (LIBM_INCLUDE_DIR AND LIBM_LIBRARIES)

mark_as_advanced(
        HAVE_LIBM
        LIBM_LIBRARIES
        LIBM_INCLUDE_DIR
)
