#include <arpa/inet.h>
#include <ctype.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

pthread_mutex_t lock;
pthread_cond_t  cond;

typedef struct _ProdInfo {
    int               num;
    struct _ProdInfo *next;
} ProdInfo;

ProdInfo *head = NULL; //定义头结点

int beginnum = 1000;

void *productor( void *arg ) {
    while ( 1 ) {
        //生产
        ProdInfo *ptr = (ProdInfo *) malloc( sizeof( ProdInfo ) );
        ptr->num = beginnum++;
        pthread_mutex_lock( &lock ); //加锁
        //头插法
        ptr->next = head;
        head = ptr;
        printf( "--------%s------tid-----%lu-------num---%d\n", __FUNCTION__, pthread_self(), ptr->num );
        pthread_mutex_unlock( &lock );
        //唤醒
        pthread_cond_signal( &cond ); //唤醒至少一个线程
        sleep( rand() % 3 );
    }
}

void *customer( void *arg ) {
    ProdInfo *ptr = NULL;
    //消费
    while ( 1 ) {
        pthread_mutex_lock( &lock );           //先加锁
        while ( head == NULL ) {               //此处为什么使用while,防止饼被吃完
            pthread_cond_wait( &cond, &lock ); //等待条件满足1. 释放锁，2. 阻塞线程等待条件满足 3. 被唤醒之后去抢锁
        }
        ptr = head;
        head = head->next; //从链表上取一个节点
        printf( "--------%s------tid-----%lu-------num---%d\n", __FUNCTION__, pthread_self(), ptr->num );
        pthread_mutex_unlock( &lock );
        free( ptr );
        sleep( rand() % 3 );
    }
}

int main() {
    pthread_mutex_init( &lock, NULL );
    pthread_cond_init( &cond, NULL );
    // 创建线程
    pthread_t tid[3];
    pthread_create( &tid[0], NULL, productor, NULL );
    pthread_create( &tid[1], NULL, customer, NULL );
    pthread_create( &tid[2], NULL, customer, NULL );

    pthread_join( tid[0], NULL );
    pthread_join( tid[1], NULL );
    pthread_join( tid[2], NULL );
    pthread_mutex_destroy( &lock );
    pthread_cond_destroy( &cond );
    return 0;
}
