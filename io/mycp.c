#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("using message:./a.out filea fileb\n");
    exit(1);
  }

  struct stat sb;
  int ret = lstat(argv[1], &sb);
  mode_t mode = umask(sb.st_mode);

  int fd1 = open(argv[1], O_RDONLY);
  int fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC);
  if (-1 == fd1) {
    printf("can't open %s\n", argv[1]);
    exit(1);
  }
  if (-1 == fd2) {
    printf("can't write %s\n", argv[2]);
    exit(1);
  }
  char buf[4096] = {0};
  int readCount = 0;
  while ((readCount = read(fd1, buf, 4096)) > 0) {
    //printf("readCount=%d\n",readCount);
    write(fd2, buf, readCount);
    memset(buf, 0, 4096);
  }
  close(fd2);
  close(fd1);
  return 1;
}
