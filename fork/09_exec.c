/*************************************************************************
    > File Name: exec.c
    > Author: YeKai
    > Company: www.itcast.cn 
    > Created Time: 2017年06月30日 星期五 23时44分30秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
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
