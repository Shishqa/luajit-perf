#ifndef BUFFER
#define BUFFER

#include <stdint.h>
#include <stddef.h>

struct buffer {
  uint8_t* data;
  uint8_t* pos;
  size_t size;
  int fd;
};

void init_buf(struct buffer* buf, int fd);

#endif /* ifndef BUFFER */
