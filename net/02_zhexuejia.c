#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define _COUNT_  5 
pthread_mutex_t kuaizi[_COUNT_];

void *zhexuejia(void *arg)
{
    int i = (int)arg;
    int left,right;
    //先决定每个哲学家对应的筷子,也就是互斥锁是哪2个?
    if(i == 0 ){
        left = 0;
        right = _COUNT_-1;
    }else{
        left = i;
        right = i-1;
    }

    while(1){

        //如何让不同的哲学家不被饿死
        if(i < _COUNT_-1 ){
            //先锁左手,再锁右手
            pthread_mutex_lock(&kuaizi[left]);
            pthread_mutex_lock(&kuaizi[right]);
            printf("i=====%d....%lu....eating\n",i,pthread_self());
            pthread_mutex_unlock(&kuaizi[right]);
            pthread_mutex_unlock(&kuaizi[left]);
            sleep(rand()%5);
            printf("i======%d,%lu....thinking....\n",i,pthread_self());

        }
        else if(i == _COUNT_-1 ){
            //先锁右手，再锁左手
            pthread_mutex_lock(&kuaizi[right]);
            pthread_mutex_lock(&kuaizi[left]);
            printf("i=====%d,%lu....eating\n",i,pthread_self());
            pthread_mutex_unlock(&kuaizi[left]);
            pthread_mutex_unlock(&kuaizi[right]);
            sleep(rand()%5);
            printf("i=====%d,%lu....thinking....\n",i,pthread_self());
        }
    }
}

int main()
{
    pthread_t tid[_COUNT_];
    int i =0;
    for(i = 0; i < _COUNT_; i ++){
        pthread_mutex_init(&kuaizi[i],NULL);
    }
    for(i = 0 ; i < _COUNT_ ; i ++){
        pthread_create(&tid[i],NULL,zhexuejia,(void*)i);
    }

    for(i = 0 ; i < _COUNT_ ; i ++){
        pthread_join(tid[i],NULL);
    }

    return 0;
}
