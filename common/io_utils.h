#ifndef CREED_INCLUDED_IO_UTILS_H
#define CREED_INCLUDED_IO_UTILS_H

#include <sys/types.h>
#include <string>

inline bool io_sync(int fd) {
  return fsync(fd) == 0;
}

size_t io_read(int fd, char *p, size_t n, size_t min = 0);

void io_write(int fd, const char *p, size_t n);

#endif