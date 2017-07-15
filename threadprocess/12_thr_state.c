#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void *thr(void *arg)
{
    printf("I am thread,tid=%lu\n",pthread_self());
}

int main()
{
    pthread_attr_t attr;
    pthread_attr_init(&attr);//属性初始化
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);//设置属性分离
    pthread_t tid;
    pthread_create(&tid,&attr,thr,NULL);

    sleep(1);
    
    int ret = pthread_join(tid,NULL);
    if(ret > 0){
        printf("ret=%d,msg:%s\n",ret,strerror(ret));
    }

    pthread_attr_destroy(&attr);//销毁线程属性
    pthread_exit(NULL);
    return 0;
}

