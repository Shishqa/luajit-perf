#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "luajit-2.1/lauxlib.h"
#include "luajit-2.1/luajit.h"
#include "luajit-2.1/lualib.h"

enum CONSTANTS { STACKTRACE_DEPTH = -100 };

void profile_callback(void* data, lua_State* L, int samples, int vmstate) {
  size_t dumpstr_len = 0;
  FILE* stacktrace = (FILE*) data;

  const char* stack_dump =
      luaJIT_profile_dumpstack(L, "F;", STACKTRACE_DEPTH, &dumpstr_len);

  fprintf(stacktrace, "%s\n", stack_dump);
  fflush(stacktrace);
}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    printf("usage: %s lua-script stacktrace_output\n", argv[0]);
  }

  printf("pid: %d\n", getpid());

  FILE* stacktrace = fopen(argv[2], "w");
  assert(stacktrace != NULL);

  lua_State* L = luaL_newstate();
  assert(NULL != L);
  luaL_openlibs(L);

  luaJIT_profile_start(L, "f", profile_callback, (void*)stacktrace);

  int error = luaL_loadfile(L, argv[1]) || lua_pcall(L, 0, 0, 0);
  if (error) {
    fprintf(stderr, "%s", lua_tostring(L, -1));
    lua_pop(L, 1); /* pop error message from the stack */
  }

  luaJIT_profile_stop(L);

  lua_close(L);
  fclose(stacktrace);
  return 0;
}
