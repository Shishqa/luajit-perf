#include <fcntl.h>

#include "benchmark/benchmark.h"
#include "luajit-2.1/lualib.h"
#include "luajit-2.1/lauxlib.h"
#include "luajit-2.1/luajit.h"
#include "luajit-2.1/lj_system_profile.h"

void prologue(lua_State* L) {
  int fd = open("out.unfold", O_WRONLY | O_CREAT);  // TODO cleaner implementation
  
  struct profiler_opt opt = {};
  opt.interval = 10;

  profile_start(L, &opt, fd);
}

void epilogue(lua_State* L) {
  L = L;
  profile_stop();
}

int main() {
  run_benchmark(prologue, epilogue);
  return 0;
}
