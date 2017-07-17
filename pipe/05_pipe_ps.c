#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int fd[2];
    pipe(fd);

    pid_t pid = fork();

    if (pid > 0)
    {
        //parent
        //重定向 输入  ---> 管道的读端
        close(fd[1]); //父进程关闭写端
        printf("parent:pid=%d", getpid());
        dup2(fd[0], STDIN_FILENO);
        execlp("grep", "grep", "bash", "--color=auto", NULL);
    }
    else if (pid == 0)
    {
        //son
        //exec ps aux
        close(fd[0]); //子进程关闭读端
        printf("son:pid=%d", getpid());
        //需要先重定向 输出--》管道的写端
        dup2(fd[1], STDOUT_FILENO);
        //execlp
        execlp("ps", "ps", "aux", NULL);
    }
    return 0;
}