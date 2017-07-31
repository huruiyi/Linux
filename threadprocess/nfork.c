#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
  pid_t pid;
  int i = 0;
  for (i = 0; i < 5; i++) {
    pid = fork();
    if (pid == 0) {
      break;
    }
  }
  while (1) {
    printf("wahahaha\n");
    sleep(i + 4);
  }
  return 0;
}
