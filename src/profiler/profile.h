#ifndef PROFILE
#define PROFILE

#include "buffer.h"
#include "luajit-2.1/lauxlib.h"

typedef enum {
  N,I,C,G,J,STATE_MAX
} vmstate;

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


