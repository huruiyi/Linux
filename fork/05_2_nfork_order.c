#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    int i;
    for (i = 0; i < 5; i++)
    {
        //父进程的出口
        pid = fork();
        if (pid == 0)
            break; //如果是子进程，退出循环，不再执行fork
    }
    //如何让父进程最后退，子进程按顺序退
    sleep(i); //每个进程在这里都睡觉

    if (i < 5)
    {
        //子进程
        printf("I am %d son,pid=%d,ppid=%d\n", i, getpid(), getppid());
    }
    else
    {
        //parent
        printf("I am parent,pid=%d,ppid=%d\n", getpid(), getppid());
    }
    return 0;
}
