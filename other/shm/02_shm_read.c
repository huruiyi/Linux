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
    //printf( "%d\n", BUFSIZ ); //8092
    int   shmid;
    char *viraddr;
    shmid = shmget( 0x1234, BUFSIZ, 0666 | IPC_CREAT );
    viraddr = (char *) shmat( shmid, 0, 0 );
    printf( "Get Message:%s", viraddr );
    shmdt( viraddr );
    shmctl( shmid, IPC_RMID, 0 );
    return EXIT_SUCCESS;
}