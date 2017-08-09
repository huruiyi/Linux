#include <signal.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int   n;
pid_t pid, ppid;

void catchsig( int num ) {
    sleep( 1 );
    printf( "%d: parent\n", n = n + 2 );
    kill( pid, SIGUSR2 );
}

void catchsig2( int num ) {
    sleep( 1 );
    printf( "%d: child\n", n = n + 2 );
    kill( ppid, SIGUSR1 );
}

int main( int argc, char *argv[] ) {
    struct sigaction act;
    act.sa_flags = 0;
    sigemptyset( &act.sa_mask );

    pid = fork();
    if ( pid > 0 ) {
        act.sa_handler = catchsig;
        sigaction( SIGUSR1, &act, NULL );
        n = 0;
        sleep( 1 );
        kill( pid, SIGUSR2 );
        while ( 1 )
            ;
    } else if ( pid == 0 ) {
        act.sa_handler = catchsig2;
        sigaction( SIGUSR2, &act, NULL );
        ppid = getppid();
        n = -1;
        while ( 1 )
            ;
    }

    return 0;
}
