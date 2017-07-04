#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
int main(int argc,char *argv[])
{

     pid_t pid;
    int i;
    for(i = 0; i < 5; i ++)
    {
        pid = fork();
        if(pid == 0)break;//子进程退出循环的出口
    }
    if(i<5)
    {
        printf("I am son,pid=%d,ppid=%d\n",getpid(),getppid());
    }
    if(i==5)
    {
         printf("I am parent,pid=%d,ppid=%d\n",getpid(),getppid());
    }

    // int i=0;
    // for(i = 0;i < 1;i ++)
    // {
    //     pid_t pid = fork();
    //      if(pid > 0)
    //     {
    //          sleep(1);
    //         printf("i=%02d, 子进程Id=%04d  ,  当前进程Id=%d  ,  父进程Id=%d\n",i,pid,getpid(),getppid());
           
    //     }
    //     else if(pid==0)
    //     {
    //          //break;
    //         printf("i=%02d, 子进程Id=%04d  ,  当前进程Id=%d  ,  父进程Id=%d\n",i,pid,getpid(),getppid());
    //     }
    //     printf("\n");
    // }
    return 0;
}