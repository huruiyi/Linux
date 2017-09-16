#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//如果open时没有使用O_NONBLOCK参数，我们发现不论读端还是写端先打开，先打开者都会阻塞，一直阻塞到另一端打开。
int main(int argc,char *argv[])
{
    int fd;

    if(argc < 2)
    {
        fprintf(stderr,"usage : %s argv[1].\n",argv[0]);
        exit(EXIT_FAILURE);
    }

    if(mkfifo(argv[1],0666) < 0 && errno != EEXIST)
    {
        fprintf(stderr,"Fail to mkfifo %s : %s.\n",argv[1],strerror(errno));
        exit(EXIT_FAILURE);
    }

    if((fd = open(argv[1],O_WRONLY|O_NONBLOCK)) < 0)
    {
        fprintf(stderr,"Fail to open %s : %s.\n",argv[1],strerror(errno));
        exit(EXIT_FAILURE);
    }

    printf("open for write success.\n");
    return 0;
}
