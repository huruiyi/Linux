#include <stdio.h>
#include <unistd.h>

int main() {
  pid_t pid;
  int i;
  for (i = 0; i < 5; i++) {
    //父进程的出口
    pid = fork();
    if (pid == 0) {
      printf("I am son,pid=%d,ppid=%d\n", getpid(), getppid());
      break; //子进程退出循环的出口
    } else if (pid > 0) {
      printf("I am parent,pid=%d,ppid=%d\n", getpid(), getppid());
    }
  }
  sleep(30);
  // ps -jax| grep 06_nfork
  // 6333   7315   7315   6333 pts/4      7315 S+    1000   0:00 ./06_nfork
  // 7315   7316   7315   6333 pts/4      7315 S+    1000   0:00 ./06_nfork
  // 7315   7317   7315   6333 pts/4      7315 S+    1000   0:00 ./06_nfork
  // 7315   7318   7315   6333 pts/4      7315 S+    1000   0:00 ./06_nfork
  // 7315   7319   7315   6333 pts/4      7315 S+    1000   0:00 ./06_nfork
  // 7315   7320   7315   6333 pts/4      7315 S+    1000   0:00 ./06_nfork

  return 0;
}
