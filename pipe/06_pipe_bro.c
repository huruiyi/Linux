#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int fd[2];
    pipe(fd);
    int i = 0;
    for (i = 0; i < 2; i++)
    {
        pid_t pid = fork();
        if (pid == 0)
            break;
    }
    if (i == 0)
    {
        //哥哥
        close(fd[0]);               //关闭读
        dup2(fd[1], STDOUT_FILENO); //标准输出重定向到管道写端
        execlp("ps", "ps", "aux", NULL);
    }
    else if (i == 1)
    {
        //弟弟
        close(fd[1]);              //关闭写
        dup2(fd[0], STDIN_FILENO); //标准输入重定向到读端
        execlp("grep", "grep", "bash", "--color=auto", NULL);
    }
    else if (i == 2)
    {
        //爹
        close(fd[0]);
        close(fd[1]);
        wait(NULL);
        wait(NULL);
    }
    printf("haha\n");
    return 0;
}