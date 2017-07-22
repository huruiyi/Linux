//实现大小写转换
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <ctype.h>
#include <arpa/inet.h>

#define SERV_PORT 8888
int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv;
    serv.sin_family = AF_INET;                             
    serv.sin_port = htons(SERV_PORT);                           
    serv.sin_addr.s_addr  = INADDR_ANY;
    if (bind(sockfd, (struct sockaddr *)&serv, sizeof(serv)) < 0)
    {
        perror("bind err");
        exit(EXIT_FAILURE);
    }
    listen(sockfd, 128);
    struct sockaddr_in client;
    socklen_t len = sizeof(client);
    int cfd = accept(sockfd, (struct sockaddr *)&client, &len);
    char strIP[32];
    printf("new conn %s:%d\n", inet_ntop(AF_INET, &client.sin_addr.s_addr, strIP, sizeof(strIP)), ntohs(client.sin_port));
    char buf[256] = {0};
    int i;
    int ret;
    while (1)
    {
        ret = read(cfd, buf, sizeof(buf)); 
        if (ret < 0)
        {
            perror("read err");
            return -1;
        }
        else if (ret == 0)
        {
            printf("client closed\n");
            break;
        }
        else
        {
            write(cfd, buf, ret);  
        }
    }
    //6. 关闭退出
    close(cfd);
    close(sockfd);
    return 0;
}