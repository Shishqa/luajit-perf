#----------------------------------------------------------------------------#

add_library(c_payload SHARED)
target_sources(c_payload
  PRIVATE
    payload.c
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
