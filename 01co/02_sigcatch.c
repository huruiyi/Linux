#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>

void catch_sig(int num)
{
    printf("begin call %s\n",__FUNCTION__);
    sleep(10);
    printf("end call %s\n",__FUNCTION__);
}

int main()
{
    struct sigaction act;
    act.sa_flags = 0;
    act.sa_handler = catch_sig;//函数指针
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask,SIGQUIT);//添加临时要阻塞的信号
    sigaction(SIGINT,&act,NULL);
    while(1){
        sleep(1);
    }
    return 0;
}

