#include <stdio.h>
#include <unistd.h>

int var = 1000; //全局变量

int main()
{
    pid_t pid = fork();
    if (pid > 0)
    {
        //parent
        printf("I am parent,pid=%d,ppid=%d,var=%d\n", getpid(), getppid(), var);
        var = 1001;
        sleep(2);
        printf("after,I am parent,pid=%d,ppid=%d,var=%d\n", getpid(), getppid(), var);
    }
    else if (pid == 0)
    {
        //son
        sleep(1);
        printf("I am son,pid=%d,ppid=%d,var=%d\n", getpid(), getppid(), var);
        var = 1002;
        printf("after,I am son,pid=%d,ppid=%d,var=%d\n", getpid(), getppid(), var);
    }
    return 0;
}
