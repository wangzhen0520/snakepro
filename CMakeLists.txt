
cmake_minimum_required(VERSION 2.8)

project(superTool)

SET(CMAKE_C_FLAGS_DEBUG "-g -Wall")

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../)

add_executable(${CMAKE_PROJECT_NAME} superTool.c DES.c md5.c)