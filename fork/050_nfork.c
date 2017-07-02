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
            printf("I am son,pid=%d,ppid=%d\n",getpid(),getppid());
            break;//子进程退出循环的出口
        }
        else if(pid > 0)
        {
            //parent 
            printf("I am parent,pid=%d,ppid=%d\n",getpid(),getppid());
        }
    }
    return 0;
}

