project(opengl-teapot)
cmake_minimum_required(VERSION 2.8)

aux_source_directory(. SRC_LIST)

# Minimum required CMake version
cmake_minimum_required(VERSION 2.8)

# Fourier Volume Rendeing
project(RTERTUS)

# Add CMake modules
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# @OpenGL
include(Find_OpenGL)

# @GLUT
include(Find_GLUT)

# @GLEW
include(Find_GLEW)

# @X11 supporting libraries
include(Find_X11)

# @Cg NVIDIA
include(Find_Cg)

# @OpenMP
include(Find_OpenMP)

# @OpenEXR
include(Find_OpenEXR)

add_executable(${PROJECT_NAME} ${SRC_LIST})
