#include <signal.h>
#include <stdio.h>
#include <unistd.h>

/*
    //sigemptyset(), sigfillset(), 
    //sigaddset(), sigdelset(), 
    //sigismember() //判断信号是否在集合当中（是否捕获添加的信号）
    Objects  of type sigset_t must be initialized by a call to either sigemptyset() or sigfillset() 
    before being passed to the functions sigaddset(), sigdelset() and sigismember() or
       the additional glibc functions described below (sigisemptyset(), sigandset(), and sigorset()). 
        The results are undefined if this is not done.

*/
int main() {
    //Ctrl+Z  20)SIGTSTP(暂停，停止)  挂起，可恢复,,可通过kill -18 进程Id来回复
    //

    // 9)9) SIGKILL，19号信号不能被捕捉，阻塞，忽略。
    //必须先调用either sigemptyset() or sigfillset()
    //sigemptyset和sigfillset相对对应一个全部设置为0,一个全部设置为1
    //pend下面的显示看不到效果，需要设置阻塞信号集
    sigset_t proc, pend;
    sigemptyset( &proc );                  //清空
    sigaddset( &proc, SIGINT );            //Ctrl+C  2) SIGINT （终止，中断）
    sigaddset( &proc, SIGQUIT );           //Ctrl+\  3) SIGQUIT （退出）
    sigaddset( &proc, SIGTSTP );           //Ctrl+Z  20)SIGTSTP(暂停，停止)  挂起，可恢复。可通过kill -18 进程Id来恢复
    sigaddset( &proc, SIGKILL );           //9) SIGKILL ，9号不能被屏蔽
    sigaddset( &proc, SIGSEGV );           //11) SIGSEGV，kill -11 进程Id 可以被捕获
    sigprocmask( SIG_BLOCK, &proc, NULL ); //设置阻塞信号集

    //循环显示未决信号集
    while ( 1 ) {
        sigpending( &pend );
        int i = 0;
        for ( i = 1; i < 32; i++ ) {
            if ( sigismember( &pend, i ) == 1 ) {
                printf( "\n%d号信号被触发\n", i );
                //产生并且被阻塞
                printf( "1" );
            } else {
                printf( "0" );
            }
        }
        printf( "\n" );
        sleep( 1 );
    }
    return 0;
}
