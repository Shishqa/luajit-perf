#----------------------------------------------------------------------------#
cmake_minimum_required(VERSION 3.11)
#----------------------------------------------------------------------------#

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(benchmark)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_CXX_FLAGS -fno-omit-frame-pointer -g)

#----------------------------------------------------------------------------#

add_subdirectory(src)

#----------------------------------------------------------------------------#
