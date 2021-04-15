#include <fcntl.h>

#include "benchmark/benchmark.h"
#include "luajit-2.1/lua.h"
#include "luajit-2.1/lualib.h"
#include "luajit-2.1/lauxlib.h"
#include "luajit-2.1/luajit.h"
#include "luajit-2.1/lj_sysprof.h"

#include <stdio.h>
#include <stdlib.h>

void cb(void* data, lua_State* L, int samples, int vmstate) {
}

void prologue(lua_State* L) {
  int fd = open("out.unfold", O_WRONLY | O_CREAT, 0640);  // TODO cleaner implementation
  if (-1 == fd) {
    perror("open");
    exit(1);
  }

  struct lj_sysprof_options opt = {};
  opt.interval = 1;
  opt.fd = fd;

  lj_sysprof_start(L, &opt);
}

void epilogue(lua_State* L) {
  lj_sysprof_stop(L);
}

int main() {
  run_benchmark(prologue, epilogue);
  return 0;
}
