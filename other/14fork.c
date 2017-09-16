#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int i = 0;
    for ( i = 0; i < 2; i++ ) {
        fork();
        printf( "&" ); //8个进程
        //printf( "&\n" ); //6个进程
    }
    wait( NULL );
    wait( NULL );
    return 0;
}
