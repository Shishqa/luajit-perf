#----------------------------------------------------------------------------#
cmake_minimum_required(VERSION 3.11)
#----------------------------------------------------------------------------#

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(benchmark)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_C_FLAGS -fno-omit-frame-pointer)

#----------------------------------------------------------------------------#

set(LUAENV ${PROJECT_SOURCE_DIR}/.luaenv)
message("using lua env: ${LUAENV}")

#----------------------------------------------------------------------------#

add_subdirectory(src)
add_subdirectory(benchmarks)

#----------------------------------------------------------------------------#
