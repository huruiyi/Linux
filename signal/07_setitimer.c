#include <signal.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

//捕捉函数
void catchsig(int num) {
  printf("cat %d sig\n", num);
}

int main() {
  struct itimerval it = {{3, 0}, {5, 0}};
  setitimer(ITIMER_REAL, &it, NULL); //定时5s以后叫醒，然后每隔10s再叫

  signal(SIGALRM, catchsig); //注册捕捉函数

  while (1) {
    printf("who can kill me?\n");
    sleep(1);
  }
  return 0;
}
