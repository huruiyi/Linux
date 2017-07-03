/*************************************************************************
    > File Name: 08_psout.c
    > Author: YeKai
    > Company: www.itcast.cn 
    > Created Time: 2017年07月02日 星期日 15时35分17秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
int main(int argc,char *argv[])
{
    int fd = open("ps.out",O_WRONLY|O_CREAT|O_TRUNC,0666);
    if(fd < 0)
    {
        perror("open err");
        return -1;
    }
    
    //重定向
    dup2(fd,STDOUT_FILENO);

    //执行exec
    execlp("ps","ps","aux",NULL);

    close(fd);

    return 0;
}
