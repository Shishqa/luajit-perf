#include <fcntl.h>

#include "benchmark/benchmark.h"
#include "luajit-2.1/lua.h"
#include "luajit-2.1/lualib.h"
#include "luajit-2.1/lauxlib.h"
#include "luajit-2.1/luajit.h"
#include "luajit-2.1/lj_sysprof.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>

static sig_atomic_t profile_running = 0;
static int fd = 0;
static pthread_t SELF;

void start_profile(lua_State* L) {
  lua_assert(SELF == pthread_self());

  fd = open("out.unfold", O_WRONLY | O_CREAT, 0640);
  if (-1 == fd) {
    perror("open");
    exit(1);
  }

  struct lj_sysprof_options opt = {};
  opt.interval = 10;
  opt.fd = fd;

  printf("starting profiling...\n");
  lj_sysprof_start(L, &opt);
}

void stop_profile(lua_State* L) {
  lua_assert(SELF == pthread_self());

  printf("stopping profiling...\n");
  lj_sysprof_stop(L);
  close(fd);
}

void profile_switch(int signal) {
  if (0 == profile_running) {
    start_profile(thread());
  } else {
    stop_profile(thread());
  }
  profile_running = 1 - profile_running;
}

int main() {
  struct sigaction sigact = {};
  sigact.sa_handler = profile_switch;
  sigact.sa_flags = SA_RESTART;
  sigaction(SIGINT, &sigact, NULL);

  SELF = pthread_self(); 

  run_benchmark(NULL, NULL);
  return 0;
}
