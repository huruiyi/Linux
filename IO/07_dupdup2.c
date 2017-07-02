#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{

    int fd = open("07.txt",O_RDWR|O_CREAT|O_TRUNC,0666);
    
    //先备份现场
    int orgfd = dup(1);
    //重定向
    dup2(fd,1);
    printf("hello-world1\n");
    //刷新缓冲区
    fflush(stdout);
    //恢复现场
    //重定向1指向标准输出
    dup2(orgfd,1);

    printf("hello-world2\n");
    return 0;
}
