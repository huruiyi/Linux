//捕捉标准输入传送给服务器
#include <stdio.h>
#include "wrap.h"
#include <sys/epoll.h>
#include <sys/wait.h>
#include <fcntl.h>

int main()
{
    int epfd = epoll_create(1024);
    int fd = Socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(9999);
    //inet_pton(AF_INET,"127.0.0.1",&serv.sin_addr.s_addr);
    inet_pton(AF_INET,"192.168.103.54",&serv.sin_addr.s_addr);

    Connect(fd,(struct sockaddr*)&serv,sizeof(serv));

    struct epoll_event ev,events[2];
    ev.events = EPOLLIN;
    ev.data.fd = fd;
    epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&ev);
    ev.data.fd = STDIN_FILENO;

    epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&ev);
    char buf[256]={0};
    int ret;
    int flags = fcntl(STDIN_FILENO,F_GETFL);
    flags |= O_NONBLOCK;
    fcntl(STDIN_FILENO,F_SETFL,flags);
    
    ret = read(STDIN_FILENO,buf,sizeof(buf));
    printf("ret is %d\n",ret);
    while(1){
        int nread = epoll_wait(epfd,events,2,-1);
        if(nread > 0){
            int i ;
            for(i = 0; i < nread ; i ++){
                if(events[i].data.fd == STDIN_FILENO){
                    ret = read(STDIN_FILENO,buf,sizeof(buf));
                    if(ret > 0){
                        write(fd,buf,ret);//写到网络
                    }
                }else if(events[i].data.fd == fd){
                    ret = read(fd,buf,sizeof(buf));
                    if(ret < 0){
                        perror("read err");
                        return -1;
                    }else if(ret == 0){
                        printf("server closed\n");
                        close(fd);
                        return 0;
                    }
                    else{
                        write(STDOUT_FILENO,buf,ret);
                    }
                }
            }
        }
    }

    return 0;
}
