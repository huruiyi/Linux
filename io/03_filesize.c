#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("./a.out filename\n");
    return -1;
  }
  //1. open file
  int fd = open(argv[1], O_RDONLY);
  if (fd < 0) {
    perror("open err");
    exit(1);
  }
  //2. lseek 得到返回值
  int ret = lseek(fd, 0, SEEK_END);
  printf("file size is %d\n", ret);
  //3. close
  close(fd);
  return 0;
}
