#include "wrap.h"
#include <ctype.h>
#include <pthread.h>

typedef struct _ClientInfo {
    struct sockaddr_in client;
    int                cfd;
} ClientInfo;

#define _MAX_THR_ 1024

ClientInfo cInfos[_MAX_THR_];

void *thr_work( void *arg ) {
    ClientInfo *info = (ClientInfo *) arg;
    int         cfd = info->cfd;
    char        strIP[32] = {0};
    printf( "I am thread,tid=%lu,client:%s:%d\n", pthread_self(), inet_ntop( AF_INET, &info->client.sin_addr.s_addr, strIP, sizeof( strIP ) ), ntohs( info->client.sin_port ) );
    char buf[256] = {0};
    while ( 1 ) {
        int ret = read( cfd, buf, sizeof( buf ) );
        if ( ret < 0 ) {
            if ( errno == EINTR ) {
                //正常，被信号打断
                continue;
            }
            perr_exit( "read err" );
        } else if ( ret == 0 ) {
            printf( "client closed\n" ); //可以打印一下谁退出
            close( cfd );
            break;
        } else {
            int i;
            for ( i = 0; i < ret; i++ ) {
                buf[i] = toupper( buf[i] );
            }
            write( cfd, buf, ret ); //写回给客户端
        }
    }
    return NULL;
}

int main() {
    //线程属性设置
    pthread_attr_t attr;
    pthread_attr_init( &attr );
    pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_DETACHED ); //设置属性分离态

    //1. 套接字
    int fd = Socket( AF_INET, SOCK_STREAM, 0 );
    //2. 绑定地址和端口
    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_port = htons( 9999 );
    serv.sin_addr.s_addr = htonl( INADDR_ANY );
    Bind( fd, (struct sockaddr *) &serv, sizeof( serv ) );
    //3。 侦听
    Listen( fd, 128 );

    struct sockaddr_in client;
    socklen_t          len = sizeof( client );
    int                cfd;
    int                index = 0;
    //4. 循环等待链接
    while ( 1 ) {
        cfd = Accept( fd, (struct sockaddr *) &client, &len );
        if ( cfd > 0 ) {
            //说明此时有新的客户端连接
            cInfos[index].client = client;
            cInfos[index].cfd = cfd;
            pthread_t tid;
            pthread_create( &tid, &attr, thr_work, &cInfos[index++] ); //设置了属性分离，不需要回收
        }
    }
    pthread_attr_destroy( &attr ); //摧毁线程属性
    return 0;
}
