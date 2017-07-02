//回收多个子进程
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    int i;
    for(i = 0; i < 5; i ++){//父进程的出口
        pid = fork();
        if(pid == 0){
            //son 
            break;//子进程退出循环的出口
        }else if(pid > 0){
            //parent 
        }
    }
    
    //如何让父进程最后退，子进程按顺序退
    sleep(i);//每个进程在这里都睡觉
    if(i < 5){
        //子进程
        printf("I am %d son,pid=%d,ppid=%d\n",i,getpid(),getppid());
    }else{
        //parent
        printf("I am parent,pid=%d,ppid=%d\n",getpid(),getppid());
        pid_t wpid ;
        //可以调用n次 wait 回收n个进程
        //使用waitpid回收
        
        while((wpid = waitpid(-1,NULL,WNOHANG)) != -1){
            if(wpid > 0){
                printf("wait pid is %d\n",wpid);
            }
        }
        printf("wait all child ok!\n");
    }
    return 0;
}

