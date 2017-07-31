#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  pid_t pid = fork();
  if (pid > 0) {
    while (1) {
      printf("I am parent,very happy!\n");
      sleep(1);
    }
  } else if (pid == 0) {
    sleep(3);
    kill(getppid(), SIGKILL);
  }
  return 0;
}
