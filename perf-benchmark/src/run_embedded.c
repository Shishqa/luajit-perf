#include "luajit-2.1/luajit.h"
#include "luajit-2.1/lualib.h"
#include "luajit-2.1/lauxlib.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) 
{
    if (argc != 2) {
        printf("usage: %s lua-script\n", argv[0]);
    }

    lua_State* L = luaL_newstate();
    assert(NULL != L);
    luaL_openlibs(L);

    int error = luaL_loadfile(L, argv[1]) || lua_pcall(L, 0, 0, 0);
    if (error) {
        fprintf(stderr, "%s", lua_tostring(L, -1));
        lua_pop(L, 1);  /* pop error message from the stack */
    }

    lua_close(L);
    return 0;
}
