#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

//验证一下父子进程是否共享文件描述符表，父进程open一个文件，fork子进程，父子都写入数据，父亲写入，子读
//文件描述符是共享的
int main()
{
    int fd = open("./h2.txt", O_RDWR);
    if (fd >= 0)
    {
        printf("打开 成功:%d\n", fd);
    }

    char bufs[100] = {0};
    read(fd, bufs, 100);
    printf("读取的数据：%s\n", bufs);
    close(fd);

    return 1;
}
