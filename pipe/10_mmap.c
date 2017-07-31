#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  //打开一个文件
  int fd = open("mem.txt", O_RDWR | O_CREAT, 0666);
  //拓展文件 lseek
  truncate("mem.txt", 10);
  //映射区建立
  char *mem = mmap(NULL, 10, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (mem == MAP_FAILED) {
    perror("mmap err");
    return -1;
  }
  strcpy(mem, "helloworld");
  //释放映射区
  if (munmap(mem, 10) < 0) {
    perror("munmap err");
    return -1;
  }
  return 0;
}