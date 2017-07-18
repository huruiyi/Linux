#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

int main()
{
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv, client;
    bzero(&serv, sizeof(serv));
    serv.sin_port = htons(8888);
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = htonl(INADDR_ANY);

    bind(listenfd, (struct sockaddr *)&serv, sizeof(serv));

    listen(listenfd, 128);

    //epoll处理
    int epfd = epoll_create(1024);
    struct epoll_event ev, events[1024];
    ev.data.fd = listenfd;
    ev.events = EPOLLIN;
    epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev);
    char strIP[16];
    while (1)
    {
        int nread = epoll_wait(epfd, events, 1024, -1); //等待事件就绪
        int i = 0;
        for (i = 0; i < nread; i++)
        {
            //不需要遍历整个数组
            if (listenfd == events[i].data.fd && (events[i].events & EPOLLIN))
            {
                //处理连接事件
                socklen_t len = sizeof(client);
                int connfd = accept(listenfd, (struct sockaddr *)&client, &len);
                printf("new connect %s at %d\n", inet_ntop(AF_INET, &client.sin_addr.s_addr, strIP, sizeof(strIP)), ntohs(client.sin_port));
                //需要将connfd上树
                ev.data.fd = connfd;
                ev.events = EPOLLIN;
                epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &ev);
            }
            else
            {
                //普通的读事件
                int cfd = events[i].data.fd;
                char buf[256] = {0};
                int ret = read(cfd, buf, sizeof(buf));
                if (ret < 0)
                {
                    if (errno == EINTR)
                    {
                        continue;
                    }
                    perror("read err");
                    close(cfd);
                    //下树
                    ev.data.fd = cfd;
                    ev.events = EPOLLIN;
                    epoll_ctl(epfd, EPOLL_CTL_DEL, cfd, &ev);
                }
                else if (ret == 0)
                {
                    close(cfd);
                    //下树
                    ev.data.fd = cfd;
                    ev.events = EPOLLIN;
                    epoll_ctl(epfd, EPOLL_CTL_DEL, cfd, &ev);
                }
                else
                {
                    write(STDOUT_FILENO, buf, ret);
                    write(cfd, buf, ret); //反射
                }
            }
        }
    }

    return 0;
}