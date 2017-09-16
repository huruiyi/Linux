#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *cbfun( void *arg ) {
    while ( 1 ) {
        printf( "线程回调" );
    }
}

int main() {
    pthread_t pts[3];
    pthread_create( &pts[0], NULL, cbfun, NULL );
    printf( "hello thread\n" );
    pthread_join( pts[0], NULL );
    return 0;
}
