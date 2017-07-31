#include <stdio.h>
#include <unistd.h>

int main() {
  pid_t pid = fork();
  if (pid > 0) {
    while (1) {
      printf("I am parent,very happy,pid=%d,ppid=%d\n", getpid(), getppid());
      sleep(1);
    }
  } else if (pid == 0) {
    while (1) {
      printf("I am son,very happy,pid=%d,ppid=%d\n", getpid(), getppid());
      sleep(1);
    }
  }
  return 0;
}
