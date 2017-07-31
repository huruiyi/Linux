#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void *thr(void *arg) {
  int i = 0;
  while (i++ < 7) {
    printf("I am a thread(%d),tid=%lu\n", i, pthread_self());
    sleep(1);
  }
  return 0;
}
//主线程挂了，子进程就挂了
//进程中父进程挂了，自己成不受影响
int main() {
  //Once a thread has been detached, it can't be joined with pthread_join(3) or be made joinable again.
  pthread_t tid;
  pthread_create(&tid, NULL, thr, NULL);
  pthread_detach(tid); //线程分离,自动回收资源
  sleep(3);            //睡一秒等等

  return 0;
}