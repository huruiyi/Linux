#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main( int argc, char *argv[] ) {
    if ( argc != 2 ) {
        printf( "./a.out filename\n" );
        return -1;
    }
    int fd = open( argv[1], O_RDONLY );
    if ( fd < 0 ) {
        perror( "open err" );
        return -1;
    }
    int  ret = 0;
    char buf[256] = {0};
    while ( 1 ) {
        memset( buf, 0x00, sizeof( buf ) );
        ret = read( fd, buf, sizeof( buf ) );
        if ( ret > 0 ) {
            printf( "%s\n", buf );
        }
    }

    close( fd );
    return 0;
}