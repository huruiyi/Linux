#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("./a.out filename\n");
    return -1;
  }
  int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0666);
  if (fd < 0) {
    perror("open err");
    exit(1);
  }
  pid_t pid = fork();
  if (pid == 0) {
    char buf[50] = "abcdefghijklmnopqrstuvwxyz";
    write(fd, buf, strlen(buf));
    //son
    //write(fd,"hello world\n",12);
  } else if (pid > 0) {
    //parent
    sleep(1);
    char buf[256] = {0};
    lseek(fd, 10, SEEK_SET);
    int ret = read(fd, buf, sizeof(buf));
    if (ret) {
      printf("read:%s\n", buf);
    }
    wait(NULL);
  }
  return 0;
}