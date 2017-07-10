#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<signal.h>
#include<sys/types.h>

pid_t pid;
int count =0;
int flag = 0;

void cat_sig_father(int num)
{
    printf("father:%d\n",count);
    count +=2;
    kill(pid,SIGUSR2);
}
void cat_sig_child(int num)
{

    printf("child:%d\n",count);
    count +=2;
    kill(getppid(),SIGUSR1);
}

int main(int argc,char *argv[])
{

    pid = fork();
    if(pid == 0) 
    {
        count=1;
        signal(SIGUSR2,cat_sig_child);
        pid_t ppid = getppid();

        while(1) { }
    }
    else{

        usleep(10);
        count=2;
        signal(SIGUSR1,cat_sig_father);
        kill(pid,SIGUSR2);
        
         while(1) { }
    }
    return 0;
}

 