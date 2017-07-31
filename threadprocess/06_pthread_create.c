#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *thr(void *arg) {
  printf("I am thread,pid=%d,%lu\n", getpid(), pthread_self());
}

int main() {
  pthread_t tid;
  pthread_create(&tid, NULL, thr, NULL);
  printf("I am main thread,pid=%d,%lu\n", getpid(), pthread_self());
  sleep(1);
  return 0;
}