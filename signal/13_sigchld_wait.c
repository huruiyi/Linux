//使用SIGCHLD回收子进程
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

void catchsig(int num)
{
    pid_t pid;
    //不能使用wait
    //不能回收一次就结束
    // while((pid = waitpid(-1,NULL,WNOHANG)) != -1)
    while ((pid = waitpid(-1, NULL, WNOHANG)) > 0)
    {
        if (pid > 0)
        {
            printf("wait %d ok\n", pid);
        }
    }
    //pid_t pid = wait(NULL);
}

int main(int argc, char *argv[])
{
    //先屏蔽SIGCHLD信号
    sigset_t proc, oldset;
    sigemptyset(&proc);
    sigaddset(&proc, SIGCHLD);
    sigprocmask(SIG_BLOCK, &proc, &oldset); //设置阻塞信号集，同时取出原阻塞信号集

    int i;
    int n = 10;
    pid_t pid;
    for (i = 0; i < n; i++)
    {
        pid = fork();
        if (pid == 0)
        {
            break;
        }
    }

    if (i < n)
    {
        printf("I am %d child,pid=%d\n", i, getpid());
    }
    else if (i == n)
    {
        //parent
        struct sigaction act;
        act.sa_flags = 0;
        act.sa_handler = catchsig;
        sigaction(SIGCHLD, &act, NULL);
        //解除SIGCHLD信号的屏蔽
        sigprocmask(SIG_SETMASK, &oldset, NULL); //恢复现场
        //sigprocmask(SIG_UNBLOCK,&proc,NULL);//恢复现场
        while (1)
        {
            sleep(1);
        }
    }
    return 0;
}
