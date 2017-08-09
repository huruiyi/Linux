#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int count = 0;
int filecount( char *dirname ) {
    DIR *pDir = opendir( dirname );
    if ( pDir == NULL ) {
        perror( "open dir err" );
        exit( 1 );
    }
    struct dirent *pdirent = NULL;
    while ( ( pdirent = readdir( pDir ) ) ) {
        if ( pdirent->d_type == DT_DIR && strcmp( pdirent->d_name, "." ) != 0 && strcmp( pdirent->d_name, ".." ) != 0 ) {
            char newdirbuf[512] = {0};
            sprintf( newdirbuf, "%s/%s", dirname, pdirent->d_name );
            filecount( newdirbuf );
        }

        if ( pdirent->d_type == DT_REG ) {
            count++;
        }
    }
    closedir( pDir );
    return 0;
}

int main( int argc, char *argv[] ) {
    if ( argc != 2 ) {
        printf( "./a.out dir\n" );
        return -1;
    }
    filecount( argv[1] );
    printf( "count =%d\n", count );
    return 0;
}