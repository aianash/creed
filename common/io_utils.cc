#include <sys/errno.h>
#include <unistd.h>
#include "io_utils.h"

size_t io_read(int fd, char *p, size_t n, size_t min) {
  size_t total = 0;
  while(n) {
    ssize_t c = read(fd, p, n);
    if(c <= 0) {
      if(c == 0) {
        if(total >= min) break;
        // throw Creed::IndexError("Couldn't read enough (EOF)");
      }
      if(errno == EINTR) continue;
      // throw Creed::IndexError("Error reading from file", errno);
    }
    p += c;
    total += c;
    n -= c;
  }
  return total;
}

void io_write(int fd, const char *p, size_t n) {
  while(n) {
    ssize_t c = write(fd, p, n);
    if(c < 0) {
      if(errno == EINTR) continue;
      // throw Creed::IndexError("Error reading from file", errno);
    }
    p += c;
    n -= c;
  }
}