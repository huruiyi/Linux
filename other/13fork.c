#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pid = fork();
    if ( pid > 0 ) {
        usleep( 1 );
        printf( "I am father\n" );
    } else {
        printf( "I am son\n" );
    }
    return 0;
}
