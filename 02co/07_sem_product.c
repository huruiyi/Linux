#include "pub.h"
#include <semaphore.h>

sem_t blank,full;
#define _VEC_CNT_ 5 //定义容量

int queue[_VEC_CNT_];//消息队列

int beginnum = 1000; //开始值

void *productor(void *arg)
{
    int index = 0;
    while(1){
        sem_wait(&blank);//判断是否可以烙饼，blank--操作
        printf("--------%s-------tid---%lu------%d\n",__FUNCTION__,pthread_self(),beginnum);
        queue[(index++)%_VEC_CNT_] = beginnum++;
        sleep(rand()%3);
        sem_post(&full);//通知消费者有饼 full++
        sleep(rand()%3);
    }
}

void *customer(void *arg)
{
    int index = 0;
    int temindex = 0;
    while(1)
    {
        sem_wait(&full);//判断是否有饼,full--操作
        printf("--------%s-------tid---%lu------%d---index---%d\n",__FUNCTION__,pthread_self(),queue[(index++)%_VEC_CNT_],index);
        sleep(rand()%3);
        sem_post(&blank);//通知生产者有地方了，blank++操作
        sleep(rand()%3);
    }
}

int main()
{
    pthread_t tid[2];
    sem_init(&blank,0,_VEC_CNT_);
    sem_init(&full,0,0);//注意初始化为0
    pthread_create(&tid[0],NULL,productor,NULL);
    pthread_create(&tid[1],NULL,customer,NULL);

    //回收线程
    pthread_join(tid[0],NULL);
    pthread_join(tid[1],NULL);
    sem_destroy(&blank);
    sem_destroy(&full);
    return 0;
}
