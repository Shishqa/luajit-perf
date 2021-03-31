#ifndef LJ_BENCHMARK
#define LJ_BENCHMARK 

#include "luajit-2.1/lualib.h"

typedef void (*benchmark_callback)(lua_State* L);

void run_benchmark(benchmark_callback prologue, 
                   benchmark_callback epilogue);

#endif /* ifndef LJ_BENCHMARK */
