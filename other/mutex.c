#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *Cb_fun( void *arg ) {
    int i = *( (int *) arg );
    printf( "index=%d,id=%lu\n", i, pthread_self() );
    sleep( 3 );
    return NULL;
}

int main() {
    pthread_t pids[5];
    int       i = 0;
    int       agrv[5] = {0};
    for ( i = 0; i < 5; ++i ) {
        agrv[i] = i;
        pthread_create( &pids[i], NULL, Cb_fun, &agrv[i] );
    }
    for ( i = 0; i < 5; ++i ) {
        pthread_join( pids[i], NULL );
    }
    sleep( 10 );
    return 0;
}
