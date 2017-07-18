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
        {
            //son
            break; //子进程退出循环的出口
        }
        else if (pid > 0)
        {
            //parent
        }
    }
    //sleep(i);

    if (i < 5)
    {
        printf("I am %d son,pid=%d,ppid=%d\n", i, getpid(), getppid());
    }
    else
    {
        printf("I am parent,pid=%d,ppid=%d\n", getpid(), getppid());
    }
    //sleep(10);
    return 0;
}
