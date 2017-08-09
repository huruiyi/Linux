#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int var = 100;

void *thr( void *arg ) {
    //int ret = 102;// 不能用函数的变量作为返回值
    printf( "I am thread ,tid=%lu,var=%d\n", pthread_self(), var );
    var = 1001;
    printf( "I am thread ,tid=%lu,var=%d\n", pthread_self(), var );
    sleep( 2 );
    printf( "I am thread,after sleep ,tid=%lu,var=%d\n", pthread_self(), var );
    //pthread_exit((void*)102);
    return (void *) 103;
    //exit(1);
}

int main() {
    pthread_t tid;
    pthread_create( &tid, NULL, thr, NULL );
    sleep( 1 );
    var = 1002;
    sleep( 3 );
    printf( "I am main thread,var=%d\n", var );
    void *ret;
    pthread_join( tid, &ret ); //阻塞等待回收子线程
    printf( "ret=%d\n", (int) ret );
    return 0;
}
