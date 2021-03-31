#ifndef PROFILE
#define PROFILE

#include "buffer.h"
#include "luajit-2.1/lauxlib.h"

typedef enum { N = 0, I = 1, C = 2, G = 3, J = 4, STATE_MAX = 5 } vmstate;

struct profiler_data {
  uint64_t vmstate[STATE_MAX];
};

struct profiler_state {
  struct profiler_data data;
  struct buffer buf;
  lua_State* L;
  vmstate vmstate;
};

void profile_start(lua_State* L, int fd);
void profile_stop(lua_State* L);

#endif /* ifndef PROFILE */

