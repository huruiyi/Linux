//实现大小写转换
#include <arpa/inet.h>
#include <ctype.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define SERV_PORT 8888
int main() {
    int                sockfd = socket( AF_INET, SOCK_STREAM, 0 );
    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_port = htons( SERV_PORT );
    serv.sin_addr.s_addr = INADDR_ANY;
    if ( bind( sockfd, (struct sockaddr *) &serv, sizeof( serv ) ) < 0 ) {
        perror( "bind err" );
        exit( EXIT_FAILURE );
    }
    listen( sockfd, 128 );
    struct sockaddr_in client;
    socklen_t          len = sizeof( client );
    int                cfd = accept( sockfd, (struct sockaddr *) &client, &len );
    char               strIP[32];
    printf( "new conn %s:%d\n", inet_ntop( AF_INET, &client.sin_addr.s_addr, strIP, sizeof( strIP ) ), ntohs( client.sin_port ) );
    char buf[256] = {0};
    int  i;
    int  ret;
    while ( 1 ) {
        ret = read( cfd, buf, sizeof( buf ) );
        int ishw = 0;
        if ( ret < 0 ) {
            perror( "read err" );
            return -1;
        } else if ( ret == 0 ) {
            printf( "client closed\n" );
            break;
        } else {
            ishw = 1;
            int len = strlen( buf );
            for ( int i = 0; i < len / 2; i++ ) {
                char a = buf[i];
                char b = buf[len - i - 2];
                if ( a != b ) {
                    ishw = 0;
                    break;
                }
            }
            char responsebuf[300] = {0};
            buf[strlen( buf ) - 1] = '\0';
            sprintf( responsebuf, "%s%s\n", buf, ishw ? ":是回文" : ":不是回文" );
            write( cfd, responsebuf, strlen( responsebuf ) );
            memset( buf, 0, sizeof( buf ) );
        }
    }
    //6. 关闭退出
    close( cfd );
    close( sockfd );
    return 0;
}
