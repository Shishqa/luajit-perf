add_library(c_payload SHARED)
target_sources(c_payload
  PRIVATE
    c_payload.c
  )
add_custom_command(TARGET c_payload
  POST_BUILD
  COMMAND cp ARGS ${CMAKE_CURRENT_BINARY_DIR}/libc_payload.so
                  ${LUAENV}/lib/libc_payload.so
  )

add_custom_command(TARGET c_payload
  POST_BUILD
  COMMAND cp ARGS ${CMAKE_CURRENT_SOURCE_DIR}/lua_payload.lua
                  ${LUAENV}/share/luajit-2.1.0-beta3/lua_payload.lua
  )
