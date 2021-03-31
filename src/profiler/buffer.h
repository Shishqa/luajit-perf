#ifndef BUFFER
#define BUFFER

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

enum CONSTANTS { DEFAULT_BUF_SIZE = 4096 };

struct buffer {
  char* data;
  char* pos;
  size_t size;
  int fd;
};

void init_buf(struct buffer* buf, int fd, size_t size);

ssize_t write_buf(struct buffer* buf, const char* payload, size_t len);

ssize_t flush_buf(struct buffer* buf);

void release_buf(struct buffer* buf);

#endif /* ifndef BUFFER */
