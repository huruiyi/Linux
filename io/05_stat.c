#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

int main( int argc, char *argv[] ) {
    if ( argc != 2 ) {
        printf( "./a.out filename\n" );
        return -1;
    }

    struct stat sb;
    //int ret = stat(argv[1],&sb);
    int ret = lstat( argv[1], &sb );

    char fmode[11] = {0};
    //搞定文件类型
    if ( S_ISREG( sb.st_mode ) )
        fmode[0] = '-';
    if ( S_ISDIR( sb.st_mode ) )
        fmode[0] = 'd';
    if ( S_ISCHR( sb.st_mode ) )
        fmode[0] = 'c';
    if ( S_ISBLK( sb.st_mode ) )
        fmode[0] = 'b';
    if ( S_ISFIFO( sb.st_mode ) )
        fmode[0] = 'p';
    if ( S_ISLNK( sb.st_mode ) )
        fmode[0] = 'l';
    if ( S_ISSOCK( sb.st_mode ) )
        fmode[0] = 's';

    //搞定用户权限
    fmode[1] = ( S_IRUSR & sb.st_mode ) ? 'r' : '-';
    fmode[2] = ( S_IWUSR & sb.st_mode ) ? 'w' : '-';
    fmode[3] = ( S_IXUSR & sb.st_mode ) ? 'x' : '-';

    fmode[4] = ( S_IRGRP & sb.st_mode ) ? 'r' : '-';
    fmode[5] = ( S_IWGRP & sb.st_mode ) ? 'w' : '-';
    fmode[6] = ( S_IXGRP & sb.st_mode ) ? 'x' : '-';

    fmode[7] = ( S_IROTH & sb.st_mode ) ? 'r' : '-';
    fmode[8] = ( S_IWOTH & sb.st_mode ) ? 'w' : '-';
    fmode[9] = ( S_IXOTH & sb.st_mode ) ? 'x' : '-';

    //获得本地时间
    struct tm *ftm = localtime( &sb.st_mtim.tv_sec );
    char       strtimebuf[20] = {0};
    sprintf( strtimebuf, "%d月  %d %02d:%02d", ftm->tm_mon + 1, ftm->tm_mday, ftm->tm_hour, ftm->tm_min );
    printf( "%s %ld %s %s %ld %s %s\n", fmode, sb.st_nlink, getpwuid( sb.st_uid )->pw_name, getgrgid( sb.st_gid )->gr_name, sb.st_size, strtimebuf, argv[1] );

    return 0;
}
