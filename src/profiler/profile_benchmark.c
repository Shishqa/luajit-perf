#include "benchmark/benchmark.h"
#include "profile.h"
#include "luajit-2.1/lua.h"
#include "luajit-2.1/luajit.h"

void epilogue(lua_State* L) {
  profile_start(L, 0);
}

int main() {
  run_benchmark(epilogue, profile_stop);  
  return 0;
}
