#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

//pipe 进程间通信（IPC）
int main()
{
    int fd[2];
    pipe(fd);
    pid_t pid=fork();
    if(pid>0){
        //fatheri
        char buf[20]={0};
        //此处会处于阻塞状态，直到写端（fd[1]）写入f数据，才会继续往下执行
        int ret=read(fd[0],buf,sizeof(buf));
        if(ret>0){
            printf("read:%s\n",buf);
        }
       int wret = wait(NULL);
       if(wret>0)
       {
           printf("wait success :%d\n",wret);
       }
    }
    else if(pid==0){
        //son
        sleep(5);
        write(fd[1],"hello",5);
    }
    else{
        //error
    }
    return 0;
}
