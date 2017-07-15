#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

int var = 100;

void *thr(void *arg)
{
    printf("I am thread ,tid=%lu,var=%d\n",pthread_self(),var);
    var = 1001;
    printf("I am thread ,tid=%lu,var=%d\n",pthread_self(),var);
    sleep(2);
    printf("I am thread,after sleep ,tid=%lu,var=%d\n",pthread_self(),var);
    //pthread_exit(NULL);
    //return NULL;
    exit(1);
}

int main()
{
    pthread_t tid;
    pthread_create(&tid,NULL,thr,NULL);
    sleep(1);
    var = 1002;
    sleep(3);
    printf("I am main thread,var=%d\n",var);
    //pthread_exit(NULL);
    return 0;
}
