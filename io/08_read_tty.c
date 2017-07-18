#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>

#define _TRY_AGAIN_ "Please try again~"

int main(int argc, char *argv[])
{
    //int fd = open("/dev/tty",O_RDWR|O_NONBLOCK);
    int fd = open("/dev/tty", O_RDWR);
    if (fd < 0)
    {
        perror("open err");
        return -1;
    }

    //使用fcntl函数处理文件属性
    //1. 先获得文件属性
    int flags = fcntl(fd, F_GETFL);
    //2. 设置一个新的属性值
    flags |= O_NONBLOCK;
    //3. 将文件属性设置为新的属性值
    fcntl(fd, F_SETFL, flags);

    char buf[256] = {0};
    do
    {
        int ret = read(fd, buf, sizeof(buf));
        if (ret == -1)
        {
            if (errno == EAGAIN)
            {
                printf("%s,errno=%d\n", _TRY_AGAIN_, errno);
                sleep(1);
                continue;
            }
            perror("read err");

            break;
        }
        else if (ret == 0)
        {
            printf("read 0\n");
            break;
        }
        else
        {
            printf("read:%s\n", buf);
            break;
        }

    } while (1);

    close(fd);
    return 0;
}
