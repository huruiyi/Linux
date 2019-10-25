/*
 *父子进程交替数数。
 */
#include <error.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

pid_t pid;

void sig_handler_p( int sig ) //parent
{
    static int i = 1;
    printf( "pid = %d, I'm father\t%d\n", getpid(), i );
    sleep( 1 );
    i += 2;
    kill( pid, SIGUSR1 ); //为避免竞态条件出现,应该在捕捉函数内完成数数及信号发送.
}

void sig_handler_c( int sig ) //child
{
    static int i = 2;
    printf( "pid = %d, I am child\t%d\n", getpid(), i );
    sleep( 1 );
    i += 2;
    kill( getppid(), SIGUSR2 );
}

int main( void ) {
    struct sigaction newact_p, oldact_p; //父进程使用
    struct sigaction newact_c, oldact_c; //子进程使用

    //子进程响应SIGUSR1
    newact_c.sa_handler = sig_handler_c;
    sigemptyset( &newact_c.sa_mask );
    newact_c.sa_flags = 0;
    sigaction( SIGUSR1, &newact_c, &oldact_c );

    //父进程响应SIGUSR2
    newact_p.sa_handler = sig_handler_p;
    sigemptyset( &newact_p.sa_mask );
    newact_p.sa_flags = 0;
    newact_p.sa_flags |= SA_RESTART; //多加这一行可以将被信号打断的系统调用重启。
    sigaction( SIGUSR2, &newact_p, &oldact_p );

    pid = fork();
    //此时父子进程都注册了2个信号处理函数，但都只会收到其中一个信号
    //子进程只收SIGUSR1，父进程只收SIGUSR2
    if ( pid == 0 ) { //子进程
        while ( 1 )
            ;
    } else { //父进程
        raise( SIGUSR2 );
        if ( wait( NULL ) ) { //wait有可能被信号打断。
            perror( "wait error" );
        }
        //while (1);				//或者不使用wait使用这条语句也可以实现。
    }

    return 0;
}
