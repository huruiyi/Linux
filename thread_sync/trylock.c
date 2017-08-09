#include "pub.h"

pthread_mutex_t mutex;

void *thr( void *arg ) {
    usleep( 100 );
    int ret = pthread_mutex_trylock( &mutex ); //尝试加锁
    if ( ret == 0 ) {
        printf( "I am thread,tid=%lu\n", pthread_self() );
        pthread_mutex_unlock( &mutex );
    } else {
        printf( "try lock err:%d,%s\n", ret, strerror( ret ) );
    }
    return NULL;
}

int main() {
    pthread_mutex_init( &mutex, NULL );

    pthread_t tid;
    pthread_create( &tid, NULL, thr, NULL );
    pthread_mutex_lock( &mutex );
    int i = 5;
    while ( i-- ) {
        printf( "I am main thread,tid=%lu\n", pthread_self() );
        sleep( 1 );
    }
    pthread_mutex_unlock( &mutex );

    pthread_mutex_destroy( &mutex );
    return 0;
}
