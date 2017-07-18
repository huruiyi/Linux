#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    //1. open ,O_CREAT,O_RDWR
    int fd = open("xxx.avi", O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd < 0)
    {
        perror("open err");
        return -1;
    }
    //2. lseek 移动文件位置,拓展文件，至少要写一次，否则拓展失效
    lseek(fd, 1024, SEEK_END);
    write(fd, "x", 1);
    //3. close
    close(fd);
    return 0;
}
