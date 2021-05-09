#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "luajit-2.1/lauxlib.h"
#include "luajit-2.1/lua.h"
#include "luajit-2.1/luajit.h"

#include "embed.h"

static lua_State *RUNNING_STATE = NULL;

lua_State *running_lua_state() { return RUNNING_STATE; }

void run_embedded(const char *script_path, int jit, callback prologue,
                  callback epilogue) {

  lua_State *L = luaL_newstate();
  assert(NULL != L);
  RUNNING_STATE = L;

  luaL_openlibs(L);
  luaJIT_setmode(L, 0,
                 LUAJIT_MODE_ENGINE | (jit ? LUAJIT_MODE_ON : LUAJIT_MODE_OFF));

  int error = luaL_loadfile(L, script_path);
  if (error) {
    fprintf(stderr, "%s", lua_tostring(L, -1));
    lua_pop(L, 1); /* pop error message from the stack */
    lua_close(L);
    return;
  }

  if (prologue) {
    prologue(L);
  }

  error = lua_pcall(L, 0, 0, 0);
  if (error) {
    fprintf(stderr, "%s", lua_tostring(L, -1));
    lua_pop(L, 1); /* pop error message from the stack */
    lua_close(L);
    return;
  }

  if (epilogue) {
    epilogue(L);
  }

  lua_close(L);
}
