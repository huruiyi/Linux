#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int sum = 0;

void *thr1(void *arg) {
  while (1) {
    printf("hello");
    sleep(rand() % 3);
    printf("world\n");
    sleep(rand() % 3);
  }
}

void *thr2(void *arg) {
  while (1) {
    printf("HELLO");
    sleep(rand() % 3);
    printf("WORLD\n");
    sleep(rand() % 3);
  }
}

int main() {
  pthread_t tid[2];
  pthread_create(&tid[0], NULL, thr1, NULL);
  pthread_create(&tid[1], NULL, thr2, NULL);

  pthread_join(tid[0], NULL);
  pthread_join(tid[1], NULL);
  return 0;
}
