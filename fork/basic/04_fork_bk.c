#include <stdio.h>
#include <unistd.h>

/*
fork，全局变量不可以共享
读的时候共享,写的时候复制
*/
int x = 10;

int main() {
  printf("Start...........\n\n");
  pid_t fpid = fork();
  int count = 0;
  count++;
  x++;
  if (fpid < 0) {
    printf("error in fork!");
  } else if (fpid == 0) {
    printf("i am the child process, my process id is %d\n", getpid());
    printf("儿子:%d\n", x);
  } else {
    usleep(1); //睡一会让子进程先开始
    printf("i am the parent process, my process id is %d\n", getpid());
    printf("爹爹:%d\n", x);
  }
  printf("统计结果是: %d\n\n", count);

  printf("Exit...........\n\n");
  return 0;
}
