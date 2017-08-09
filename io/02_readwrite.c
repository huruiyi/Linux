#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    int fd = open( "11.log", O_RDWR | O_CREAT | O_TRUNC, 0666 );
    if ( fd < 0 ) {
        perror( "open err" );
        exit( 1 );
    }

    write( fd, "hello-world\n", 12 );
    //需要移动一下读写位置

    lseek( fd, 0, SEEK_SET );
    char buf[16] = {0};

    int ret = read( fd, buf, sizeof( buf ) );

    if ( ret ) {
        write( STDOUT_FILENO, buf, ret );
    }

    close( fd );
    return 0;
}
