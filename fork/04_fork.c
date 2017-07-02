#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("begin ....\n\n");
    pid_t pid = fork();
     
    if(pid > 0)
    {
        //parent
        printf("I am parent,sonpid=%d,pid=%d,ppid=%d\n",pid,getpid(),getppid());
        sleep(1);//等待子进程结束
    }
    else if(pid == 0)
    {
        //son 
        printf("I am son,sonpid=%d,pid=%d,ppid=%d\n",pid,getpid(),getppid());
    }
  
    printf("end ....\n");
    return 0;
}