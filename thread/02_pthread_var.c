#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int   var = 100;
void *call( void *agr ) {
    sleep( 2 );
    var = 300;
    printf( "pid=%d,tid=%lu,var=%d\n", getpid(), pthread_self(), var );
    return 0;
}
//栈私有, 堆公有
int main() {
    pthread_t thread;
    pthread_create( &thread, NULL, call, NULL );
    sleep( 1 );
    printf( "pid=%d,tid=%lu,var=%d\n", getpid(), pthread_self(), var );

    sleep( 3 );
    var = 200;
    printf( "pid=%d,tid=%lu,var=%d\n", getpid(), pthread_self(), var );

    return 0;
}