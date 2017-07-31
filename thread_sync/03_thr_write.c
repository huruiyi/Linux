#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

pthread_mutex_t lock;

char buf[20];

void *thr1(void *arg) {
  int i = 0;
  sleep(1);
  pthread_mutex_lock(&lock); //加锁
  for (; i < 20; i++) {
    usleep(rand() % 3);
    buf[i] = '0';
  }
  pthread_mutex_unlock(&lock); //解锁
  return NULL;
}

void *thr2(void *arg) {
  int i = 0;

  pthread_mutex_lock(&lock);
  for (; i < 20; i++) {
    usleep(rand() % 3);
    buf[i] = '1';
  }
  pthread_mutex_unlock(&lock);
  return NULL;
}

int main() {
  pthread_mutex_init(&lock, NULL); //锁初始化

  memset(buf, 0x00, sizeof(buf));
  pthread_t tid[2];
  pthread_create(&tid[0], NULL, thr1, NULL);
  pthread_create(&tid[1], NULL, thr2, NULL);

  pthread_join(tid[0], NULL);
  pthread_join(tid[1], NULL);
  pthread_mutex_destroy(&lock); //销毁锁
  printf("buf is %s\n", buf);
  return 0;
}
