#include "buffer.h"

void init_buf(struct buffer *buf, int fd) {
  buf->fd = fd;
}
