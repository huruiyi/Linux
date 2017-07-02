/*
 *  fork_test.c
 *  version 1
 *  Created on: 2010-5-29
 *      Author: wangth
 */
#include <unistd.h>
#include <stdio.h>
int main ()
{
    int count=0;
    printf("Start...........\n\n\n");

    pid_t fpid=fork();
    if (fpid < 0)
    {
        printf("error in fork!");
    }
    else if (fpid == 0)
    {
        printf("i am the child process, my process id is %d\n",getpid());
        printf("我是爹的儿子\n");//对某些人来说中文看着更直白。
    }
    else
    {
        printf("i am the parent process, my process id is %d\n",getpid());
        printf("我是孩子他爹\n");
    }
    count++;
    printf("统计结果是: %d\n\n",count);

    printf("Exit...........\n\n\n");
    return 0;
}
