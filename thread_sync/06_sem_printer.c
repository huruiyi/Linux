#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

sem_t sem; //定义信号量

void *thr_func(void *arg) {
  char *msg = (char *)arg;
  while (1) {
    sem_wait(&sem); //p --
    printf("in---tid---%lu----msg----%s\n", pthread_self(), msg);
    sleep(3);
    printf("away---tid---%lu----msg----%s\n", pthread_self(), msg);
    sem_post(&sem); //v ++
    sleep(rand() % 3);
  }
}

int main() {
  sem_init(&sem, 0, 5); //初始化信号量
  pthread_t tid[10];
  int i;
  for (i = 0; i < 10; i++) {
    if (i < 5) {
      pthread_create(&tid[i], NULL, thr_func, "hello"); //创建5个打印hello的线程
    } else {

      pthread_create(&tid[i], NULL, thr_func, "world"); //创建5个打印world的线程
    }
  }
  while (1) {
    printf("\n\n\n\n\n"); //没事打一下换行，为了查看清晰
    sleep(1);
  }
  for (i = 0; i < 10; i++) {
    pthread_join(tid[i], NULL);
  }
  sem_destroy(&sem); //摧毁信号量
  return 0;
}
