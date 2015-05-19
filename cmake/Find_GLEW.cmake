#####################################################################
# Copyright © 2011-2015,
# Marwan Abdellah: <abdellah.marwan@gmail.com>
#####################################################################

if(APPLE)
    # Base directory
    include_directories ("/System/Library/Frameworks")

    # Find the GLEW library
    find_library(GLEW_LIBRARY GLEW REQUIRED)

    # Advanced variable
    mark_as_advanced(GLEW_LIBRARY)

    # Adding the include directory to the systems
    set(GLEW_INCLUDE_DIR "/usr/X11R6/include/")
    include_directories(${GLEW_INCLUDE_DIR})

    # Adding the library directories
    set(GLEW_LIB_DIR "/usr/X11R6/lib")
    link_directories(${GLEW_LIB_DIR})

    # Checking if GLEW was found or not
    if(NOT GLEW_LIBRARY STREQUAL "")
        message(STATUS "GLEW Found")
        message("-- GLEW include directory : ${GLEW_INCLUDE_DIR}")
        message("-- GLEW library directory : ${GLEW_LIBRARY}")
    else(NOT GLEW_LIBRARY STREQUAL "")
        message(FATAL_ERROR "GLEW NOT Found")
    endif(NOT GLEW_LIBRARY STREQUAL "")

    # Linking against GLEW
    link_libraries(${GLEW_LIBRARY})
else(APPLE)
    # Linux
    find_path(GLEW_INCLUDE_DIR "glew.h"
      HINTS "/usr/include/GL"
        /usr/include
        /usr/local/include
        /opt/local/include
    )

    find_library(GLEW_LIBRARY NAMES GLEW
      HINTS "/usr/lib/x86_64-linux-gnu"
      PATHS
        /usr/lib
        /usr/local/lib
        /opt/local/lib
    )

    include(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(GLEW DEFAULT_MSG
                                      GLEW_LIBRARY
                                      GLEW_INCLUDE_DIR)

    if(GLEW_FOUND)
        message(STATUS "GLEW Found")
        message("-- GLEW include directory : ${GLEW_INCLUDE_DIR}")
        message("-- GLEW library directory : ${GLEW_LIBRARY}")
        include_directories(${GLEW_INCLUDE_DIR}/GL)
        link_libraries(${GLEW_LIBRARY})
    else(GLEW_FOUND)
        MESSAGE(FATAL_ERROR "GLEW NOT Found")
    endif(GLEW_FOUND)
endif(APPLE)




