#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PNUM 3
#define CNUM 5

// 结构体
struct msg {
    int         num;
    struct msg *next;
} msg;

// 设置两个空节点
struct msg *head;
struct msg *mp;

// 定义一个条件变量变量
pthread_cond_t cond;

// 定义一个互斥锁变量
pthread_mutex_t lock;

void *consumer( void *num ) {
    while ( 1 ) {
        pthread_mutex_lock( &lock ); //加锁
        while ( head == NULL ) {
            pthread_cond_wait( &cond, &lock ); //判断是否存在节点，如果存在节点，抢到节点的处理，没有抢到的继续阻塞等待
        }
        mp = head; //删除节点
        head = mp->next;
        printf( "----Consume %d ----%d\n", (int) num, mp->num );
        free( mp );
        pthread_mutex_unlock( &lock ); //解锁
        sleep( rand() % 3 );
    }
}

void *producer( void *num ) {
    while ( 1 ) {
        pthread_mutex_lock( &lock );
        mp = malloc( sizeof( struct msg ) ); //创建一个新的节点
        mp->num = rand() % 1000 + 1;
        printf( "****Producer %d****%d\n", (int) num, mp->num );

        mp->next = head; //插入链表
        head = mp;
        pthread_mutex_unlock( &lock );

        pthread_cond_signal( &cond ); //给消费者发送信号
        sleep( rand() % 5 );
    }
}
int main( void ) {
    pthread_t pid[PNUM], cid[CNUM];
    int       i = 0;

    srand( time( NULL ) ); //创建3个生产者和5个消费者
    for ( i = 0; i < PNUM; i++ ) {
        pthread_create( &pid[i], NULL, producer, (void *) i );
    }
    for ( i = 0; i < CNUM; i++ ) {
        pthread_create( &cid[i], NULL, consumer, (void *) i );
    }

    for ( i = 0; i < PNUM; i++ ) { //回收线程资源
        pthread_join( pid[i], NULL );
    }
    for ( i = 0; i < CNUM; i++ ) {
        pthread_join( cid[i], NULL );
    }
    return 0;
}
