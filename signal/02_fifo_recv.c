//通过fifo发送文件
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("./a.out fifoname desfile\n");
        return -1;
    }
    int fd = open(argv[1], O_RDONLY);
    //int fd = open(argv[1],O_WRONLY);
    if (fd < 0)
    {
        perror("open err");
        exit(1);
    }
    //sleep(10);
    int pfd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);

    char buf[512] = {0};
    int ret = 0;
    while ((ret = read(fd, buf, sizeof(buf))) > 0)
    {
        printf("read-to-write:%d\n", ret);
        write(pfd, buf, ret);
    }
    close(fd);
    close(pfd);
    return 0;
}
