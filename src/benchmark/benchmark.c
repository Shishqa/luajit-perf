#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "luajit-2.1/lauxlib.h"
#include "luajit-2.1/lua.h"
#include "luajit-2.1/luajit.h"

#include "benchmark/benchmark.h"

void run_benchmark(benchmark_callback prologue, benchmark_callback epilogue) {
  
  static const char* benchmark_script = "./src/benchmark/run_payloads.lua";

  lua_State* L = luaL_newstate();
  assert(NULL != L);
  luaL_openlibs(L);

  int error = luaL_loadfile(L, benchmark_script);
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
