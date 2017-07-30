#include <stdio.h>
#include <unistd.h>

int main() {
  pid_t pid;
  int i;
  for (i = 0; i < 5; i++) {
    pid = fork();
    if (pid == 0) {
      break;
    }
  }

  if (i < 5) {
    printf("I am %d son,pid=%d,ppid=%d\n", i, getpid(), getppid());
  } else {
    printf("I am parent,pid=%d,ppid=%d\n", getpid(), getppid());
  }
  sleep(30);
  return 0;
}
