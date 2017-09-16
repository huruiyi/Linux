#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{

    int fd[2];
    pipe(fd);
    pid_t pid=fork();
    if(pid>0)
    {
        //father
        dup2(fd[0],STDIN_FILENO);
        execlp("grep","grep","bash",NULL);
    }
    else if(pid==0)
    {
        //son
        dup2(fd[1],STDOUT_FILENO);
        // 将ps 输出的结果重定向到写端（fd[1]）
        execlp("ps","ps","aux",NULL);
    }
    return 0;
}
