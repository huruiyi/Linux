#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  //打开一个文件
  //int fd = open("mem.txt",O_RDWR|O_CREAT|O_TRUNC,0666);
  //int fd = open("mem.txt",O_WRONLY|O_CREAT|O_TRUNC,0666);
  int fd = open("mem.txt", O_RDONLY | O_CREAT | O_TRUNC, 0666);
  //拓展文件 lseek
  truncate("mem.txt", 16);
  //映射区建立
  char *mem = mmap(NULL, 16, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (mem == MAP_FAILED) {
    perror("mmap err");
    return -1;
  }
  close(fd); //映射区之后关闭
  //strcpy(mem,"helloworldhaha");
  strcpy(mem, "helloworld");
  //mem++;
  //释放映射区
  if (munmap(mem, 10) < 0) {
    perror("munmap err");
    return -1;
  }
  return 0;
}