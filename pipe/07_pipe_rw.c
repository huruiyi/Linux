#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int fd[2];
    pipe( fd );

    pid_t pid = fork();
    if ( pid == 0 ) {
        //son
        close( fd[0] );
        //close(fd[1]);
        write( fd[1], "hello\n", 6 );
        while ( 1 ) {
            sleep( 1 );
        }
    } else if ( pid > 0 ) {
        //parent
        close( fd[1] );
        close( fd[0] );

        //char buf[256]={0};
        //int ret = read(fd[0],buf,sizeof(buf));
        //printf("ret === %d\n",ret);
        //if(ret > 0)
        //{
        //    printf("read:%s",buf);
        //}
        int status;
        wait( &status );
        if ( WIFSIGNALED( status ) ) {
            printf( "child killed by %d\n", WTERMSIG( status ) );
        }
        while ( 1 ) {
            sleep( 1 );
        }
    }
    return 0;
}
