#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int i = 0;
  pid_t pid;
  for (i = 0; i < 2; i++) {
    pid = fork();
    if (pid == 0)
      break;
  }
  if (i == 0) {
    //son1'
    printf("I am %d child,pid=%d,ppid=%d\n", i, getpid(), getppid());
    //call fpe
    execl("/home/itheima/linux/0512/day06/fpe", "fpe", NULL);
  } else if (i == 1) {
    //son2
    printf("I am %d child,pid=%d,ppid=%d\n", i, getpid(), getppid());
    execlp("ps", "ps", "-u", "itheima", NULL);
  } else if (i == 2) {
    //parent
    int status;
    for (i = 0; i < 2; i++) {
      pid_t wpid = wait(&status);
      if (WIFEXITED(status)) {
        printf("child pid %d exit with %d\n", wpid, WEXITSTATUS(status));
      }
      if (WIFSIGNALED(status)) {
        printf("child pid %d killed by %d\n", wpid, WTERMSIG(status));
      }
    }
  }
  return 0;
}
