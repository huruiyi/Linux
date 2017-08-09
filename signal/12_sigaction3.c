#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void catch_sig( int num ) {
    printf( "%s begin call %d \n", __FUNCTION__, num );
    sleep( 10 );
    printf( "%s end call %d \n", __FUNCTION__, num );
}

int main() {
    struct sigaction act;
    act.sa_flags = 0;
    act.sa_handler = catch_sig;
    sigemptyset( &act.sa_mask );
    sigaction( SIGINT, &act, NULL ); //补货ctrl+c

    while ( 1 ) {
        printf( "lai da wo ya !\n" );
        sleep( 1 );
    }
    return 0;
}
