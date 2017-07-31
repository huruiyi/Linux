#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int fd = fcntl(STDOUT_FILENO, F_DUPFD, 0);

  write(fd, "hello\n", 6);
  return 0;
}