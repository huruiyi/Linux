#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    //0x00001234 3604489    hvm        666        8192       1

    //0x00001234 3637257    hvm        666        8192       1
    //0x00000000 3637257    hvm        666        8192       1          目标   
    int   shmid;
    char *viraddr = NULL;
    char  buffer[BUFSIZ];

    shmid = shmget( 0x1234, BUFSIZ, 0666 | IPC_CREAT );
    viraddr = (char *) shmat( shmid, 0, 0 );

    while ( 1 ) {
        puts( "请输入:" );
        fgets( buffer, BUFSIZ, stdin );
        strcat( viraddr, buffer );
        if ( strncmp( buffer, "end", 3 ) == 0 ) {
            break;
        }
    }
    shmdt( viraddr );
    return EXIT_SUCCESS;
}