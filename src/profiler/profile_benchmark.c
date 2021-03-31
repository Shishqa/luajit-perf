#include <fcntl.h>

#include "benchmark/benchmark.h"
#include "luajit-2.1/lua.h"
#include "luajit-2.1/luajit.h"
#include "profile.h"

void epilogue(lua_State* L) {
  int fd = open("out.unfold", O_WRONLY | O_CREAT);  // TODO cleaner implementation
  profile_start(L, fd);
}

int main() {
  run_benchmark(epilogue, profile_stop);
  return 0;
}
