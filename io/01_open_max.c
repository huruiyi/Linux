#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  char filename[512] = {0};
  int i = 3;
  while (1) {
    sprintf(filename, "temp_%04d", i++);
    int fd = open(filename, O_RDONLY | O_CREAT, 0666);
    if (fd < 0) {
      perror("open err");
      break;
    }
  }
  printf("i=%d\n", i);
  return 0;
}
