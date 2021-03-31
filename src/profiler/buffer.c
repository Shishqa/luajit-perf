#include "buffer.h"

void init_buf(struct buffer* buf, int fd, size_t size) {
  buf->fd = fd;
  buf->pos = 0;
  buf->size = size;
  buf->data = (uint8_t*)calloc(size, sizeof(uint8_t));
}

void release_buf(struct buffer* buf) { free(buf->data); }

ssize_t flush_buf(struct buffer* buf) {
  ssize_t bytes = write(buf->fd, buf->data, buf->pos - buf->data);
  buf->pos = buf->data;

  return bytes;
}

ssize_t write_buf(struct buffer* buf, const uint8_t* payload, size_t len) {
  size_t total_bytes = 0;

  while (len != 0) {
    size_t available_space = buf->size - (buf->pos - buf->data);

    size_t chunck_size = available_space > len ? len : available_space;
    memcpy(buf->pos, payload, chunck_size);

    buf->pos += chunck_size;
    payload += chunck_size;
    total_bytes += chunck_size;
    len -= chunck_size;

    if (buf->pos - buf->data == buf->size) {
      if (-1 == flush_buf(buf)) {
        return -1;
      }
    }
  }

  return total_bytes;
}
