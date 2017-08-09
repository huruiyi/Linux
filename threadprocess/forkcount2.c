#include <signal.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int n;

void catchsig( int num ) {
    printf( "%d: parent\n", n = n + 2 );
}

void catchsig2( int num ) {
    printf( "%d: child\n", n = n + 2 );
}

int main( int argc, char *argv[] ) {
    struct sigaction act;
    act.sa_flags = 0;
    sigemptyset( &act.sa_mask );

    pid_t pid = fork();
    if ( pid > 0 ) {
        act.sa_handler = catchsig;
        sigaction( SIGUSR1, &act, NULL );
        n = 0;
        sleep( 1 );
        while ( 1 ) {
            printf( "parent\n" );
            kill( pid, SIGUSR2 );
            //这个sleep不管用？
            sleep( 2 );
        }
    } else if ( pid == 0 ) {
        act.sa_handler = catchsig2;
        sigaction( SIGUSR2, &act, NULL );
        pid_t ppid = getppid();
        n = -1;
        while ( 1 ) {
            sleep( 2 );
            kill( ppid, SIGUSR1 );
        }
    }

    return 0;
}
