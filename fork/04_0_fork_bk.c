#include <unistd.h>
#include <stdio.h>

 
/*
fork，全局变量不可以共享
读的时候共享,写的时候复制
*/
int x=10;

int main ()
{
    printf("Start...........\n\n\n");
    int count=0;
    pid_t fpid=fork();
    if (fpid < 0)
    {
        printf("error in fork!");
    }
    else if (fpid == 0)
    {
        printf("i am the child process, my process id is %d\n",getpid());
        printf("我是爹的儿子\n");//对某些人来说中文看着更直白。
        ++x;
        printf("儿子:%d\n",x);
    }
    else
    {
        printf("i am the parent process, my process id is %d\n",getpid());
        printf("我是孩子他爹\n");
        ++x;
        printf("爹爹:%d\n", x);
    }
    count++;
    printf("统计结果是: %d\n\n",count);

    printf("Exit...........\n\n\n");
    return 0;
}
