# add_library(profile)
# target_sources(profile
#   PRIVATE
#     profile.h
#     buffer.h
#     write.h
#     callchain.h
#     profile.c
#     buffer.c
#     write.c
#     callchain.c
#   )
# target_include_directories(profile
#   PUBLIC
#     ${PROJECT_SOURCE_DIR}/include/
#     ${PROJECT_SOURCE_DIR}/.luaenv/include/
#   )
# target_link_libraries(profile
#   PUBLIC
#     ${PROJECT_SOURCE_DIR}/.luaenv/lib/libluajit.a
#     m
#     dl
#   )


add_executable(prof_bench profile_benchmark.c)
target_link_libraries(prof_bench
  PRIVATE
    benchmark
  )


