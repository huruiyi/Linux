#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main( int argc, char *argv[] ) {
    // const char * file1="/home/huruiyi/桌面/12.txt";
    // const char * file2="/home/huruiyi/桌面/13.txt";

    const char *file1 = "/home/huruiyi/桌面/a.iso";
    const char *file2 = "/home/huruiyi/桌面/b.iso";
    int         fdSrc = open( file1, O_RDONLY );
    int         fdDes = open( file2, O_RDWR | O_CREAT, 0664 );

    int         i = 0;
    struct stat sb;
    int         red = stat( file1, &sb );
    truncate( file2, sb.st_size );

    int totalCount = 500;

    long int pSize = sb.st_size / totalCount;
    long int lastSize = sb.st_size % totalCount;

    const long int lastpSize = pSize + lastSize;
    for ( i = 0; i < totalCount; i++ ) {
        pid_t pid = fork();
        if ( pid == 0 )
            break;
    }

    if ( i < totalCount - 1 ) {
        long int r = 0;
        long int w = 0;
        char *   buf = (char *) malloc( sizeof( char ) * pSize );

        long long offset = pSize * i;
        lseek( fdSrc, offset, SEEK_SET );
        r = read( fdSrc, buf, pSize );

        lseek( fdDes, offset, SEEK_SET );
        w = write( fdDes, buf, pSize );
        printf( "i=%03d\tpid=%05d,read:%ld  write:%ld\t", i, getpid(), r, w );
    }
    if ( i == totalCount - 1 ) {
        long int  r = 0;
        long int  w = 0;
        long long offset = pSize * i;
        char *    buf = (char *) malloc( sizeof( char ) * lastpSize );
        lseek( fdSrc, offset, SEEK_SET );
        r = read( fdSrc, buf, lastpSize );

        lseek( fdDes, offset, SEEK_SET );
        w = write( fdDes, buf, lastpSize );
        printf( "i=%03d\tpid=%05d,read:%ld  write:%ld\t", i, getpid(), r, w );
    }

    if ( i == totalCount ) {
        for ( i = 0; i < totalCount; i++ ) {
            int pid = wait( NULL );
            printf( "进程%d关闭\n", pid );
        }
    }
    close( fdSrc );
    close( fdDes );
    return 0;
}