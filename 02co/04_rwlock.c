#include "pub.h"

pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;//初始化，可以不用调用init

int beginnum = 1000;//模拟的共享资源

void *thr_write(void *arg)
{
    while(1)
    {
        pthread_rwlock_wrlock(&rwlock);//加写锁
        printf("-----%s-----tid-------%lu------%d\n",__FUNCTION__,pthread_self(),++beginnum);
        usleep(1);
        pthread_rwlock_unlock(&rwlock);//释放锁
        usleep(5000);
    }

}
void *thr_read(void *arg)
{
    while(1)
    {
        pthread_rwlock_rdlock(&rwlock);//加读锁
        printf("-----%s-----tid-------%lu------%d\n",__FUNCTION__,pthread_self(),beginnum);
        usleep(2);
        pthread_rwlock_unlock(&rwlock);//释放锁
        usleep(2000);
    }
}

int main()
{
    int i;
    pthread_t tid[8];
    for(i = 0 ; i < 5; i ++)
    {
        pthread_create(&tid[i],NULL,thr_read,NULL);
    }
    for( ; i < 8; i ++)
    {
        pthread_create(&tid[i],NULL,thr_write,NULL);
    }


    for(i = 0 ; i < 8; i ++)
    {
        pthread_join(tid[i],NULL);
    }
    pthread_rwlock_destroy(&rwlock);
    return 0;
}
