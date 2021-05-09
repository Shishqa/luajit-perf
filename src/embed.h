#ifndef EMBED_LJ
#define EMBED_LJ

#include "luajit-2.1/lualib.h"

typedef void (*callback)(lua_State *L);

void run_embedded(const char *script_path, int jit,
                  callback prologue, callback epilogue);

lua_State *running_lua_state();

#endif /* ifndef EMBED_LJ */
