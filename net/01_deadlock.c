#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t lk1, lk2;

void *thr(void *arg) {
  printf("-----%s----%lu---%d--begin lock1\n", __FUNCTION__, pthread_self(), __LINE__);
  pthread_mutex_lock(&lk1); //尝试加锁1
  printf("-----%s----%lu---%d---get lock1 ok\n", __FUNCTION__, pthread_self(), __LINE__);
  sleep(2); //确保main线程能抢到锁2

  printf("-----%s----%lu---%d---begin lock2\n", __FUNCTION__, pthread_self(), __LINE__);
  pthread_mutex_lock(&lk2); //尝试加锁2
  printf("-----%s----%lu---%d---get lock2 ok\n", __FUNCTION__, pthread_self(), __LINE__);
}

int main() {
  pthread_mutex_init(&lk1, NULL); //互斥量初始化
  pthread_mutex_init(&lk2, NULL);

  pthread_t tid;
  pthread_create(&tid, NULL, thr, NULL); //创建线程thr
  sleep(1);                              //确保线程thr能抢到lk1

  printf("-----%s----%lu---%d---begin lock2\n", __FUNCTION__, pthread_self(), __LINE__);
  pthread_mutex_lock(&lk2); //main线程抢锁2
  printf("-----%s----%lu---%d---get lock2 ok\n", __FUNCTION__, pthread_self(), __LINE__);

  printf("-----%s----%lu---%d---begin lock1\n", __FUNCTION__, pthread_self(), __LINE__);
  pthread_mutex_lock(&lk1); //main线程抢锁1
  printf("-----%s----%lu---%d---get lock1 ok\n", __FUNCTION__, pthread_self(), __LINE__);

  pthread_join(tid, NULL);     //线程回收
  pthread_mutex_destroy(&lk1); //互斥量销毁
  pthread_mutex_destroy(&lk2);
  return 0;
}
