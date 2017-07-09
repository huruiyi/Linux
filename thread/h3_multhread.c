#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

pthread_mutex_t lock;
int sum=0;

void *thr1(void *arg)
{
    while(1)
    {
    pthread_mutex_lock(&lock);
        printf("hello");
        sleep(rand()%2);
        printf("world\n");
        sleep(rand()%2);
    pthread_mutex_unlock(&lock);
    }
}

void *thr2(void *arg)
{
    while(1)
    {
    pthread_mutex_lock(&lock);
        printf("HELLO");
        sleep(1);
        printf("WORLD\n");
        sleep(1);
    pthread_mutex_unlock(&lock);
    }
}


int main()
{
    pthread_mutex_init(&lock,NULL);
    pthread_t tid[2];
    pthread_create(&tid[0],NULL,thr1,NULL);
    pthread_create(&tid[1],NULL,thr2,NULL);

    pthread_join(tid[0],NULL);
    pthread_join(tid[1],NULL);

    pthread_mutex_destroy(&lock);
    return 0;
}
