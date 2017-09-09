#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {

    int i = 0;
    for ( i = 0; i < 3; ++i ) {
        pid_t ret = fork();
        if ( ret == 0 ) {
            printf( "子进程%d---pid=%d\n", i, getpid() );
            break;
        } else {
            printf( "父进程%d---pid=%d\n", i, getpid() );
        }
    }
    sleep( 10 );
    return 0;
}
