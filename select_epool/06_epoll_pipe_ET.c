#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <string.h>

//验证epoll的ET模式
int main()
{
    int fd[2];
    pipe(fd); //管道初始化

    pid_t pid = fork();
    if (pid == 0) //child
    {
        close(fd[0]);
        char buf[11] = {0};
        int i = 0;
        char ch = 'A';
        while (1)
        {
            memset(buf, ch, sizeof(buf) - 1);
            write(fd[1], buf, strlen(buf));
            ch++;
            sleep(3);
        }
    }
    else
    {
        //father
        close(fd[1]);
        int epfd = epoll_create(1024); //创建根节点
        struct epoll_event ev, evs;
        ev.events = EPOLLIN | EPOLLET; //监控读,边缘触发
        ev.data.fd = fd[0];
        epoll_ctl(epfd, EPOLL_CTL_ADD, fd[0], &ev); //添加到树上

        char buf[5] = {0};
        while (1)
        {
            int nread = epoll_wait(epfd, &evs, 1, -1);
            printf("read ... ===%d\n", nread);
            if (nread > 0)
            {
                int ret = read(evs.data.fd, buf, sizeof(buf));
                if (ret > 0)
                {
                    printf("read:%s\n", buf);
                }
            }
        }
    }
    return 0;
}