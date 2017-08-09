#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *thr( void *arg ) {
    //int num = (int)arg;
    int num = *(int *) arg;
    printf( "I am %d thread,pid=%d,tid=%lu\n", num, getpid(), pthread_self() );
}

int main() {
    pthread_t tid[5];
    int       i;
    for ( i = 0; i < 5; i++ ) {
        pthread_create( &tid[i], NULL, thr, (void *) &i );
    }
    sleep( 1 );
    return 0;
}
