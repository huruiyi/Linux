#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#include<pthread.h>

void * cal(void *arg)
{
    int i=*((int *)arg);
    printf("Index=%d ,tid=%lu, proId=%d\n",i,pthread_self(),getpid());
    return NULL;
}
 struct A{
    int *p;
    int b;
};
typedef struct A SA;
int main(int argc,char * argv[])
{
    pthread_t thread[5]; ;
    int index[5]={0,1,2,3,4};
    int *p=(int *)malloc(sizeof(int));
    int a=12;
 
    for(int i=0;i<5;i++)
    {
        *p=123;
        pthread_create(&thread[i],NULL,cal,p);
    }
    sleep(1);
    return 0;
}

 