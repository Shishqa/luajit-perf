#----------------------------------------------------------------------------#

add_library(c_payload SHARED)
target_sources(c_payload
  PRIVATE
    c_payload.c
  )
add_custom_command(TARGET c_payload
  POST_BUILD
  COMMAND cp ARGS ${CMAKE_CURRENT_BINARY_DIR}/libc_payload.so
                  ${CMAKE_SOURCE_DIR}/.luaenv/lib/libc_payload.so
  )

#----------------------------------------------------------------------------#

add_library(benchmark)
target_sources(benchmark
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include/benchmark/benchmark.h
  PRIVATE
    benchmark.c
  )
target_include_directories(benchmark
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include/
    ${PROJECT_SOURCE_DIR}/.luaenv/include/
  )
target_link_libraries(benchmark
  PUBLIC
    ${PROJECT_SOURCE_DIR}/.luaenv/lib/libluajit.a
    m
    dl
  )

add_custom_command(TARGET benchmark
  POST_BUILD
  COMMAND cp ARGS ${CMAKE_SOURCE_DIR}/src/benchmark/lua_payload.lua
                  ${CMAKE_SOURCE_DIR}/.luaenv/share/luajit-2.1.0-beta3/lua_payload.lua
  )


#----------------------------------------------------------------------------#

add_executable(run_benchmark run_benchmark.c)
target_link_libraries(run_benchmark
  PRIVATE
    benchmark
  )

#----------------------------------------------------------------------------#
