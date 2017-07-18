#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("./a.out filename\n");
        return -1;
    }
    printf("begin open.....\n");
    int fd = open(argv[1], O_WRONLY);
    if (fd < 0)
    {
        perror("open err");
        return -1;
    }
    printf("end open.......\n");
    char buf[256] = {0};
    int num = 1;
    while (1)
    {
        sprintf(buf, "xiaoming%03d", num++);
        write(fd, buf, strlen(buf));
        sleep(1);
    }

    close(fd);
    return 0;
}