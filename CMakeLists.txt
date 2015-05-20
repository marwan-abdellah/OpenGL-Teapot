project(opengl-teapot)
cmake_minimum_required(VERSION 2.8)

aux_source_directory(. SRC_LIST)

# Add CMake modules
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# @OpenGL
include(Find_OpenGL)

# @GLUT
include(Find_GLUT)

# @GLEW
include(Find_GLEW)

add_executable(${PROJECT_NAME} ${SRC_LIST})
