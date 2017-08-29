#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int fd[2];
    pipe( fd );
    int i = 0;
    for ( i = 0; i < 2; ++i ) {
        pid_t ret = fork();
        if ( ret == 0 ) {
            printf( "子进程%d\n", i );
            break;
        } else {
            printf( "父进程%d\n", i );
        }
    }
    printf( "i=%d---  ppid=%d.......pid=%d\n", i, getppid(), getpid() );

    printf( "\n" );
    sleep( 10 );
    return 0;
}

// i=0---  ppid=34294.......pid=34295
// i=1---  ppid=34294.......pid=34296

// i=2---  ppid=32549.......pid=34294

// 32549  34294  34294  32549 pts/7     34294 S+    1000   0:00 ./a.out

// 34294  34295  34294  32549 pts/7     34294 S+    1000   0:00 ./a.out
// 34294  34296  34294  32549 pts/7     34294 S+    1000   0:00 ./a.out
