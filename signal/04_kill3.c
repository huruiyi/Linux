#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int i;
  pid_t pid, pid3 = 0;
  for (i = 0; i < 5; i++) {
    pid = fork();
    if (pid == 0) {
      break;
    }
    if (i == 2) {
      pid3 = pid; //记录第三号进程编号
    }
  }

  if (i < 5) {
    while (1) {
      printf("I am %d child,pid=%d\n", i, getpid());
      sleep(1);
    }
  } else {
    sleep(3);
    printf("%d\n", pid3);
    kill(pid3, SIGKILL);
    while (1) {
      sleep(1);
    }
  }
  return 0;
}
