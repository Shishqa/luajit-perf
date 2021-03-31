/*============================================================================*/

#include "luajit-2.1/lauxlib.h"
#include "luajit-2.1/luajit.h"
#include "luajit-2.1/lualib.h"

#include "profile.h"
#include "buffer.h"
#include "write.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

static struct profiler_state profiler_state;

void init_profiler_state(struct profiler_state* ps, int fd) {
  init_buf(&ps->buf, fd);
  ps->vmstate = 0;
  memset(ps->data.vmstate, 0, sizeof(ps->data.vmstate));
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef void (*stacktrace_func)(struct profiler_state* ps);

static stacktrace_func stacktrace_handlers[] = {
  write_vmstate,  
  write_vmstate,  
  write_vmstate,  
  write_vmstate,  
  write_vmstate,  
  write_vmstate
};

void write_stack(struct profiler_state* ps) {
  stacktrace_func handler;
  handler = stacktrace_handlers[ps->vmstate];
  assert(NULL != handler);
  handler(ps);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void profile_callback(void* data, lua_State* L, int samples, int vmstate) {
  struct profiler_state* ps = (struct profiler_state*)(data);

  /*
  size_t dumpstr_len = 0;
  FILE* stacktrace = (FILE*) data;

  const char* stack_dump =
      luaJIT_profile_dumpstack(L, "F;", STACKTRACE_DEPTH, &dumpstr_len);

  fprintf(stacktrace, "%s\n", stack_dump);
  fflush(stacktrace);
  */

  switch (vmstate) {
    case 'N':
      ps->vmstate = N;
      break;
    case 'I':
      ps->vmstate = I;
      break;
    case 'C':
      ps->vmstate = C;
      break;
    case 'G':
      ps->vmstate = G;
      break;
    case 'J':
      ps->vmstate = J;
      break;
    default:
      assert("unreachable");
      break;
  }

  ps->data.vmstate[ps->vmstate]++;
  ps->L = L;

  write_stack(ps);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
// API

void profile_start(lua_State* L, int fd) {
  struct profiler_state* ps = &profiler_state;
  init_profiler_state(ps, fd);

  luaJIT_profile_start(L, "f", profile_callback, ps);
}

void profile_stop(lua_State* L) {
  luaJIT_profile_stop(L);

  struct profiler_state* ps = &profiler_state;

  for (size_t state = 0; state <= STATE_MAX; ++state) {
    printf("State %lu -> %lu\n", state, ps->data.vmstate[state]);
  }
  print_counters();
}

/*============================================================================*/
