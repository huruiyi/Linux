/*************************************************************************
    > File Name: 01_mycp.c
    > Author: YeKai
    > Company: www.itcast.cn 
    > Created Time: 2017年06月30日 星期五 22时32分30秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
int main(int argc,char *argv[])
{
    if(argc != 3){
        printf("./a.out src des\n");
        return -1;
    }
    char buf[1024]={0};
    int fdsrc = open(argv[1],O_RDONLY);
    int fddes = open(argv[2],O_WRONLY|O_CREAT,0666);
    if(fdsrc == -1 || fddes == -1){
        perror("open src or des err");
        exit(1);
    }
    int ret = 0;
    while((ret = read(fdsrc,buf,sizeof(buf)))){
        write(fddes,buf,ret);
    }
    printf("cp %s to %s ok\n",argv[1],argv[2]);
    close(fdsrc);
    close(fddes);
    return 0;
}

