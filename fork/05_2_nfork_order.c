#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    int i;
    for(i = 0; i < 5; i ++)
    {
        //父进程的出口
        pid = fork();
        if(pid == 0)
        {
            //son
            break;//子进程退出循环的出口
        }
        else if(pid > 0)
        {
            //parent
        }
    }
    
    //如何让父进程最后退，子进程按顺序退
    sleep(i);//每个进程在这里都睡觉
    printf("i=%d\t",i);
    if(i < 5)
    {
        //子进程
        printf("I am %d son,pid=%d,ppid=%d\n",i,getpid(),getppid());
    }
    else
    {
        //parent
        printf("I am parent,pid=%d,ppid=%d\n",getpid(),getppid());
    }
    return 0;
}
