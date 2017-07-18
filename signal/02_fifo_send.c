//通过fifo发送文件
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    printf("hello1\n");
    if (argc != 3)
    {
        printf("./a.out fifoname sendfile\n");
        return -1;
    }
    printf("hello2,%s\n", argv[1]);
    // int fd = open(argv[1],O_WRONLY);
    int fd = open(argv[1], O_WRONLY);
    printf("hello3\n");
    if (fd < 0)
    {
        perror("open err");
        exit(1);
    }

    printf("hello4\n");
    int pfd = open(argv[2], O_RDONLY);

    printf("hello\n");
    char buf[256] = {0};
    int ret = 0;
    while ((ret = read(pfd, buf, sizeof(buf))) > 0)
    {
        printf("read:%d\n", ret);
        write(fd, buf, ret);
    }
    close(fd);
    close(pfd);
    return 0;
}
