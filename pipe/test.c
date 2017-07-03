#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

pid_t sonPid[2];
int main()
{
    pid_t pid;
    int i;
    int fd[2];
    pipe(fd);
    for(i = 0; i < 2; i ++)
    {
        //父进程的出口
        pid = fork();
        if(pid == 0)
        {
            //son
            printf("儿子进程创建成功---pid=%d\n",pid);
            break;//子进程退出循环的出口
        }
        else if(pid > 0)
        {
            //parent
            printf("父进进程创建成功---pid=%d\n",pid);
        }
    }
    
    //如何让父进程最后退，子进程按顺序退
    sleep(i);
    //每个进程在这里都睡觉
    printf("i=%d\n",i);
    if(i < 2)
    {
        //子进程
        printf("I am %d son,pid=%d,ppid=%d\n",i,getpid(),getppid());

        if(i==0)
        {
            sonPid[0]=getpid();
            close(fd[0]);//子进程关闭读端
            //需要先重定向 输出--》管道的写端
            dup2(fd[1],STDOUT_FILENO);
            //execlp 
            execlp("ps","ps","aux",NULL);
        }
        if(i==1)
        {
            sonPid[1]=getpid();
            
            close(fd[1]);//父进程关闭写端
            dup2(fd[0],STDIN_FILENO);
            execlp("grep","grep","bash","--color=auto",NULL);
        }
    }
    else
    {
        // printf("回收！！");
        close(fd[0]);
        close(fd[1]);
        // wait(NULL);
        // wait(NULL);
        sleep(1);

        for(int i=0;i<2;i++)
        {
            int status;
            pid_t wpid =0;
            while((wpid=waitpid(sonPid[i],&status,WNOHANG)) == 0)
            {
                //代表子进程一直没有推出
                sleep(1);
            }
            printf("I am parent,pid=%d,wpid=%d\n",getpid(),wpid);
            if(WIFEXITED(status))
            {
                //代表正常退出
                printf("child exit with %d\n",WEXITSTATUS(status));
            }
            if(WIFSIGNALED(status))
            {
                //代表被信号杀死
                printf("child killed by %d\n",WTERMSIG(status));
            }
        }
        
    }
    
    sleep(1);
    return 0;
}
