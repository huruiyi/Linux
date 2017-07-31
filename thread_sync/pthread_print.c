#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t lock;

int sum = 0;

void *thr1(void *arg) {

  while (1) {
    pthread_mutex_lock(&lock); //加锁
    printf("hello");
    sleep(rand() % 3);
    printf("world\n");
    pthread_mutex_unlock(&lock); //解锁
    sleep(rand() % 3);
  }
}

void *thr2(void *arg) {
  while (1) {

    pthread_mutex_lock(&lock); //加锁
    printf("HELLO");
    sleep(rand() % 3);
    printf("WORLD\n");
    pthread_mutex_unlock(&lock); //解锁
    sleep(rand() % 3);
  }
}

int main() {
  pthread_mutex_init(&lock, NULL); //初始化
  pthread_t tid[2];
  pthread_create(&tid[0], NULL, thr1, NULL);
  pthread_create(&tid[1], NULL, thr2, NULL);

  pthread_join(tid[0], NULL);
  pthread_join(tid[1], NULL);
  pthread_mutex_destroy(&lock);
  return 0;
}
