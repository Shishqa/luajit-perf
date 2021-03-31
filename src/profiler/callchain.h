#include <execinfo.h>

#include "luajit-2.1/luajit.h"
#include "profile.h"

void dump_callchain_lfunc(struct profiler_state* ps);

void dump_callchain_ffunc(struct profiler_state* ps);

void dump_callchain_cfunc(struct profiler_state* ps);

void dump_callchain_trace(struct profiler_state* ps);

// TODO vmstate?
