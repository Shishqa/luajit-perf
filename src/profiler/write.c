#include "write.h"

#include <stdio.h>

static struct test test;

void print_counters() {
  printf(
      "counters:\n"
      "\tlfunc: %lu\n"
      "\tffunc: %lu\n"
      "\tcfunc: %lu\n"
      "\tinterp: %lu\n"
      "\ttrace: %lu\n",
      test.lfunc, test.ffunc, test.cfunc, test.interp, test.trace);
}

void write_trace(struct profiler_state* ps) { test.trace++; }

void write_lfunc(struct profiler_state* ps) {
  test.lfunc++;
  dump_callchain_lfunc(ps);
}

void write_ffunc(struct profiler_state* ps) {
  test.ffunc++;
  //dump_callchain_ffunc(ps);
}

void write_cfunc(struct profiler_state* ps) {
  test.cfunc++;
  //dump_callchain_cfunc(ps);
}

void write_vmstate(struct profiler_state* ps) { test.interp++; }

