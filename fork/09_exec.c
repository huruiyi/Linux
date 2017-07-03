#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>

/*
    A 、 两个进程直接不可以共享同一个全局变量
    B 、 execl函数是根据查找指定路径来执行对应的程序
    C 、 子进程执行完execlp之后，父子进程地址空间中的代码段是不同的
    D 、 一般情况下exec族函数都是和fork一起使用的
*/

int main(int argc,char *argv[])
{
    //1.execl
    printf("1--------------\n");
    //execl("/bin/ps","ps","-o","pid,ppid,pgrp,session,comm",NULL);

    //2.execv
    char *const ps_argv[]={"ps","-o","pid,ppid,pgrp,session,comm",NULL};
    //execv("/bin/ps",ps_argv);

    //3.execle
    //char *const ps_envp[]={"PATH=/bin:/usr/bin","TERM=console",NULL};
    char *const ps_envp[]={"PATH=/bin:/home/itheima/linux/0512/day05","TERM=linux",NULL};
    //execle("hello","hello",NULL,ps_envp);
    //execle("/bin/ps","ps","-o","pid,ppid,pgrp,session,comm",NULL,ps_envp);

    //4.execlp
    //execlp("ps","ps","-o","pid,ppid,pgrp,session,comm",NULL);

    //5.execvp
    //execvp("ps",ps_argv);
    
    //6.execvpe
    execvpe("ps",ps_argv,ps_envp);
    return 0;
}
