#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int fd[2];
    pipe( fd );
    int i = 0;
    for ( i = 0; i < 2; ++i ) {
        pid_t pid = fork();
        if ( pid == 0 ) {
            printf( "son for i=%d--- pid=%d ppid=%d.......%d\n", i, pid, getpid(), getppid() );
            break;
        } else {
            printf( "father for i=%d--- pid=%d ppid=%d.......%d\n", i, pid, getpid(), getppid() );
        }
    }
    if ( i == 0 ) {
        //son1
        printf( "%d----%d\n", i, getpid() );
        close( fd[0] );
        dup2( fd[1], STDOUT_FILENO );
        execlp( "ps", "ps", "aux", NULL );
    } else if ( i == 1 ) {
        //son2
        printf( "%d----%d\n", i, getpid() );
        close( fd[1] );
        dup2( fd[0], STDIN_FILENO );
        execlp( "grep", "grep", "bash", NULL );
    } else if ( i == 2 ) {
        close( fd[0] );
        close( fd[1] );
        wait( NULL );
        wait( NULL );
        //parent
        printf( "%d----%d\n", i, getpid() );
    } else {
        printf( "end......\n" );
    }
    return 0;
}
