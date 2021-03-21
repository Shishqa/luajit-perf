#----------------------------------------------------------------------------#

add_library(c_payload SHARED)
target_sources(c_payload
  PRIVATE
    payload.c
  )
add_custom_command(TARGET c_payload
  POST_BUILD
  COMMAND cp ARGS ${CMAKE_CURRENT_BINARY_DIR}/libc_payload.so
                  ${CMAKE_SOURCE_DIR}/lib/libc_payload.so
  )

#----------------------------------------------------------------------------#

add_executable(run_embedded run_embedded.c)
target_include_directories(run_embedded
  PRIVATE
    ${PROJECT_SOURCE_DIR}/include/
  )
target_link_libraries(run_embedded
  PRIVATE
    ${PROJECT_SOURCE_DIR}/lib/libluajit.a
    m
    dl
  )

#----------------------------------------------------------------------------#
