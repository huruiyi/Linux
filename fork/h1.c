#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

//创建2个进程，一个子进程执行自己编写的程序（段错误，或者浮点型错误），另外调用系统命令 
int main()
{
    pid_t pid=fork();
    if(pid>0)
    {
        //parent
        printf("当前进程Id:%d,父进程Id:%d,子进程Id：%d\n",getpid(),getppid(),pid);
        sleep(1);
        char* const arg[] ={"hello","0"};
        execve("./hello",arg,NULL);
    }
    else if(pid==0)
    {
        //son
        printf("当前进程Id:%d,父进程Id:%d，son\n",getpid(),getppid());
        char *const ps_argv[]={"ps","-o","pid,ppid,pgrp,session,comm",NULL};
        execv("/bin/ps",ps_argv);
    }
}
