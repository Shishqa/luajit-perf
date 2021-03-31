#include "callchain.h"

void dump_callchain_lfunc(struct profiler_state* ps) {
  size_t dumpstr_len = 0;
  const char* stack_dump =
      luaJIT_profile_dumpstack(ps->L, "F;", INT32_MIN, &dumpstr_len);

  write_buf(&ps->buf, stack_dump, dumpstr_len);
  write_buf(&ps->buf, "\n", 1);
}

void dump_callchain_cfunc(struct profiler_state* ps) {
  const int depth = backtrace(ps->backtrace_buf, DEFAULT_BUF_SIZE);

  char** names = backtrace_symbols(ps->backtrace_buf, depth);

  for (size_t i = 0; i < depth; ++i) {
    write_buf(&ps->buf, names[i],
              strlen(names[i]));  // FIXME definetely will cause massive
                                  // profiling overhead
    write_buf(&ps->buf, ";", 1);
  }
  write_buf(&ps->buf, "\n", 1);
}

void dump_callchain_ffunc(struct profiler_state* ps) {
  // dump_callchain_cfunc(ps);
}

