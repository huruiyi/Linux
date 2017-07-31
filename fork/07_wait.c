#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/*
    A 、 wait和waitpid作用是进程资源回收
    B 、 wait是阻塞函，waitpid可以设置阻塞和非阻塞
    C 、 waitpid可指定回收某个进程资源
    D 、 wait或waitpid调用一次只能清理一个子进程
*/
int main() {
  pid_t pid = fork();
  if (pid > 0) {
    //parent
    printf("I am parent,pid=%d\n", getpid());
    int status;
    pid_t wpid = wait(&status);
    printf("I am parent,pid=%d,wpid=%d\n", getpid(), wpid);
    if (WIFEXITED(status)) {
      //代表正常退出
      printf("child exit with %d\n", WEXITSTATUS(status));
    }
    if (WIFSIGNALED(status)) {
      //代表被信号杀死
      printf("child killed by %d\n", WTERMSIG(status));
    }
    while (1) {
      printf("I am very happy!\n");
      sleep(1);
    }
  } else if (pid == 0) {
    //son
    printf("I am child,pid=%d,ppid=%d,I will die\n", getpid(), getppid());
    //exit(99);
    //int a = 10;
    //int b=a/0;//除0错误
    while (1) {
      printf("I am child,pid=%d\n", getpid());
      sleep(1);
    }
  }
  return 100;
}
