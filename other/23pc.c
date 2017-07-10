#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

pthread_mutex_t lock;
pthread_cond_t cond;

typedef struct _ProdInfo{
    int num;
    struct _ProdInfo *next;
}ProdInfo;

ProdInfo * head = NULL; 

int beginnum = 1000;
 
void *productor (void *arg)
{
    while(1)
    {
        ProdInfo *ptr = (ProdInfo *)malloc(sizeof(ProdInfo));
        ptr->num = beginnum++;
        pthread_mutex_lock(&lock); 
        
        ptr->next = head;
        head = ptr;
        printf("--------%s------tid-----%lu-------num---%d\n",__FUNCTION__,pthread_self(),ptr->num);
        pthread_mutex_unlock(&lock);
        
        pthread_cond_signal(&cond); 
        sleep(rand()%3);
    }
}
 
void *customer(void *arg)
{
    ProdInfo *ptr = NULL;
    while(1)
    {
        pthread_mutex_lock(&lock);//先加锁
        while(head == NULL)
        {    
            pthread_cond_wait(&cond,&lock); 
        }
        ptr = head;
        head=head->next;//从链表上取一个节点
        printf("--------%s------tid-----%lu-------num---%d\n",__FUNCTION__,pthread_self(),ptr->num);
        pthread_mutex_unlock(&lock);
        free(ptr);
        sleep(rand()%3);
    }
}

int main()
{
    pthread_mutex_init(&lock,NULL);
    pthread_cond_init(&cond,NULL);

    pthread_t tid[8];
    pthread_create(&tid[0],NULL,productor,NULL);
    pthread_create(&tid[1],NULL,productor,NULL);
    pthread_create(&tid[2],NULL,productor,NULL);


    pthread_create(&tid[3],NULL,customer,NULL);
    pthread_create(&tid[4],NULL,customer,NULL);
    pthread_create(&tid[5],NULL,customer,NULL);
    pthread_create(&tid[6],NULL,customer,NULL);
    pthread_create(&tid[7],NULL,customer,NULL);


    for(int i=0;i<7;i++)
    {
        pthread_join(tid[i],NULL);
    }
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
    return 0;
}
