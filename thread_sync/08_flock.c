#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define filename "/home/itheima/temp.lock" //为什么要写绝对路径？确定为同一个文件

int main()
{
    int fd = open(filename,O_RDWR,0664);
    if(fd < 0)
    {
        perror("open file err");
        exit(1);
    }
    struct flock lk;
    lk.l_type = F_WRLCK;//如果是读锁可行吗?
    lk.l_start = 0;
    //lk.l_whence = SEEK_END;
    lk.l_whence = SEEK_SET;
    lk.l_len  = 0;//len代表加锁长度,0代表整个文件

    if(fcntl(fd,F_SETLK,&lk) < 0)
    {
        perror("fcntl err");
        exit(1);
    }
    
    while(1)
    {
        sleep(1);
        printf("I am sleep %d\n",getpid());
    }
    close(fd);
    return 0;
}

