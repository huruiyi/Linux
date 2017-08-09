#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void *thr( void *arg ) {
    while ( 1 ) {
        pthread_testcancel();
        //        printf("I am a thread,tid=%lu\n",pthread_self());
        //        sleep(1);
    }
}

int main() {
    pthread_t tid;
    pthread_create( &tid, NULL, thr, NULL );

    sleep( 3 );
    pthread_cancel( tid ); //杀死线程
    void *ret;
    pthread_join( tid, &ret ); //回收
    printf( "tid out with %d\n", (int) ret );
    return 0;
}
