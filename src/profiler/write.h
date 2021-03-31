#ifndef WRITE
#define WRITE

#include <stdint.h>
#include "profile.h"
#include "callchain.h"

struct test {
  uint64_t lfunc;
  uint64_t ffunc;
  uint64_t cfunc;
  uint64_t interp;
  uint64_t trace;
};

void print_counters();

void write_trace(struct profiler_state* ps);
void write_lfunc(struct profiler_state* ps);
void write_ffunc(struct profiler_state* ps);
void write_cfunc(struct profiler_state* ps);
void write_vmstate(struct profiler_state* ps);

#endif /* ifndef WRITE */
