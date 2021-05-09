#----------------------------------------------------------------------------#

add_executable(run_embedded 
  embed.h
  embed.c
  main.c
  )

target_include_directories(run_embedded
  PUBLIC
    ${PROJECT_SOURCE_DIR}/src/
    ${PROJECT_SOURCE_DIR}/.luaenv/include/
  )

target_link_libraries(run_embedded
  PUBLIC
    ${PROJECT_SOURCE_DIR}/.luaenv/lib/libluajit.a
    m
    dl
  )

#----------------------------------------------------------------------------#
