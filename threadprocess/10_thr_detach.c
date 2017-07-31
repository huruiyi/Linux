#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void *thr(void *arg) {
  printf("I am a thread,tid=%lu\n", pthread_self());
}

int main() {
  pthread_t tid;
  pthread_create(&tid, NULL, thr, NULL);
  pthread_detach(tid); //线程分离
  sleep(1);            //睡一秒等等
  int ret = pthread_join(tid, NULL);
  if (ret > 0) {
    printf("errno=%d,msg:%s\n", ret, strerror(ret));
  }
  return 0;
}
