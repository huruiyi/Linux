#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include <signal.h>
#include<sys/types.h>
pid_t pid;
int count =0;
int flag = 0;

void cat_sig_father(int num)
{
//    sleep(1);
//    flag = 1;
    printf("%d\n",count);
    count +=2;
    kill(pid,SIGUSR2);
}
void cat_sig_child(int num)
{
//    sleep(1);
//    flag = 1;
    printf("%d\n",count);
    count +=2;
     kill(getppid(),SIGUSR1);
}

int main(int argc,char *argv[])
{

    pid = fork();
    if(pid == 0) {
        //son
        count=1;
        signal(SIGUSR2,cat_sig_child);
        pid_t ppid = getppid();

        while(1){
            if(flag == 1){
     //           kill(ppid,SIGUSR1);
        //        flag = 0;
            }
        }
    }
    else{

        usleep(10);
        count=2;
        signal(SIGUSR1,cat_sig_father);
        kill(pid,SIGUSR2);
        //printf("begin ...\n");
        while(1){
            if(flag == 1){
           //     kill(pid,SIGUSR2);
           //     flag = 0;
            }
        }

    }
    return 0;
}
