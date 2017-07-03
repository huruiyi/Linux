#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

//验证一下父子进程是否共享文件描述符表，父进程open一个文件，fork子进程，父子都写入数据，父亲写入，子读
//文件描述符是共享的
int main()
{
    int fd=open("./h2.txt",O_RDWR); 
    pid_t pid=fork();
    if(pid>0)
    {
        //parent
        printf("当前进程Id:%d,父进程Id:%d,子进程Id：%d\n",getpid(),getppid(),pid);
        //必须睡一会才能读到数据
        sleep(1);
        if(fd>=0)
        {
            printf("打开 成功:%d\n",fd);
            char buf[50]={"abcdefg123456"};
            int wcount=write(fd,buf,strlen(buf));
            printf("写入个数:%d\n",wcount);
        }
    }
    else if(pid==0)
    {
        //son
        printf("当前进程Id:%d,父进程Id:%d，son\n",getpid(),getppid());
        char bufs[100]={0};
        read(fd,bufs,sizeof(bufs));
        printf("子进程读取的数据：%s\n",bufs);
    }
   
    return 1;
}
