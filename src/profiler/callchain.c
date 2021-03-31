#include "callchain.h"

void dump_callchain_lfunc(struct profiler_state* ps) {
  size_t dumpstr_len = 0;
  const char* stack_dump =
      luaJIT_profile_dumpstack(ps->L, "F;", INT32_MIN, &dumpstr_len);

  write_buf(&ps->buf, stack_dump, dumpstr_len);
  write_buf(&ps->buf, "\n", 1);
}

