#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int fd = open("dup.txt", O_RDONLY);
  int newfd = dup(fd);
  if (fd > 0) {
    printf("ok\n");
  } else {
    printf("error\n");
    exit(0);
  }
  char buf[50] = {0};
  while ((read(fd, buf, 50) > 0)) {
    printf("%s", buf);
    memset(buf, 0, sizeof(buf));
  }
  printf("+++++++++++++++++++++++read from "
         "newfd++++++++++++++++++++++++++++++++++++\n");
  lseek(newfd, 0, SEEK_SET);
  while ((read(newfd, buf, 50) > 0)) {
    printf("%s", buf);
    memset(buf, 0, sizeof(buf));
  }
  return 0;
}
