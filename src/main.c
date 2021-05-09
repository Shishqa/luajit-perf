#include <fcntl.h>

#include "embed.h"
#include "luajit-2.1/lj_sysprof.h"

#include <getopt.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static sig_atomic_t profile_running = 0;
static pthread_t SELF;

static struct lj_sysprof_options SYSPROF_OPT = {};

const char *mode_leaf = "leaf";
const char *mode_callgraph = "callgraph";

void start_profile(lua_State *L) {
  lua_assert(SELF == pthread_self());
  printf("starting profiler...\n");
  lj_sysprof_start(L, &SYSPROF_OPT);
}

void stop_profile(lua_State *L) {
  lua_assert(SELF == pthread_self());
  printf("stopping profiler...\n");
  lj_sysprof_stop(L);
}

void profile_switch(int signal) {
  if (0 == profile_running) {
    start_profile(running_lua_state());
  } else {
    stop_profile(running_lua_state());
  }
  profile_running = 1 - profile_running;
}

int main(int argc, char *argv[]) {
  SYSPROF_OPT.interval = 99;
  SYSPROF_OPT.mode = PROFILE_CALLGRAPH;

  char const *out_file = "sysprof.bin";
  int use_jit = 1;

  int opt = -1;
  while ((opt = getopt(argc, argv, "m:i:o:j:")) != -1) {
    switch (opt) {
    case 'm': {
      if (optarg && !strncmp(optarg, mode_leaf, sizeof(*mode_leaf))) {
        SYSPROF_OPT.mode = PROFILE_LEAF;
      } else if (optarg &&
                 !strncmp(optarg, mode_callgraph, sizeof(*mode_callgraph))) {
        SYSPROF_OPT.mode = PROFILE_CALLGRAPH;
      } else {
        SYSPROF_OPT.mode = PROFILE_DEFAULT;
      }
    } break;
    case 'i':
      SYSPROF_OPT.interval = strtol(optarg, NULL, 10);
      break;
    case 'o':
      out_file = optarg;
      break;
    case 'j':
      if (optarg && !strncmp(optarg, "on", 2)) {
        use_jit = 1;
      } else if (optarg && !strncmp(optarg, "off", 3)) {
        use_jit = 0;
      } else {
        fprintf(stderr, "bad -j option\n");
        exit(1);
      }
    default:
      break;
    }
  }

  const char *script_path = argv[optind];
  if (!script_path) {
    fprintf(stderr, "script_path is not specified");
    exit(1);
  }

  int fd = open(out_file, O_WRONLY | O_CREAT, 0640);
  if (-1 == fd) {
    perror("open");
    exit(1);
  }
  SYSPROF_OPT.fd = fd;

  struct sigaction sigact = {};
  sigact.sa_handler = profile_switch;
  sigact.sa_flags = SA_RESTART;
  sigaction(SIGINT, &sigact, NULL);

  SELF = pthread_self();

  printf("running %s\n\n"
         "jit: %s\n"
         "profiler: \n"
         "  out: %s\n"
         "  interval: %d\n"
         "  mode: %s\n\n",
         script_path, use_jit ? "ON" : "OFF", out_file, SYSPROF_OPT.interval,
         SYSPROF_OPT.mode == PROFILE_LEAF      ? "LEAF"
         : SYSPROF_OPT.mode == PROFILE_DEFAULT ? "DEFAULT"
                                               : "CALLGRAPH");

  run_embedded(script_path, use_jit, NULL, lj_sysprof_stop);

  close(SYSPROF_OPT.fd);

  return 0;
}
