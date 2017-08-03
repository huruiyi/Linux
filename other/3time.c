#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int main() {
    clock_t t1, t2;
    time_t  now;
    time( &now );
    printf( "It is now %s", ctime( &now ) );
    t1 = clock(); //起始时间
    for ( int i = 10; i >= 1; i-- ) {
        printf( "%2d/n", i );
        sleep( 1000 );
    }
    t2 = clock();                           //结束时间
    printf( "%ld\n", ( t2 - t1 ) / 1000 ); // CLK_TCK=1000
    time( &now );
    printf( "It is now %s", ctime( &now ) );
    printf( "The strlen is %zd/n", strlen( ( ctime( &now ) ) ) );
    return EXIT_SUCCESS;
}