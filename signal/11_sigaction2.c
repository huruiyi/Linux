#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

void catchsig(int num)
{
    printf("cat %d sig\n", num);
    sleep(10);
    printf("%s call end\n", __FUNCTION__);
}

int main()
{
    struct sigaction act;
    act.sa_flags = 0;
    act.sa_handler = catchsig;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, SIGINT); //添加SIGINT到临时屏蔽的信号
    sigaction(SIGALRM, &act, NULL);
    //设置定时器
    struct itimerval it = {{3, 0}, {4, 0}}; //4s后第一次闹钟，之后每隔3s一次闹钟
    setitimer(ITIMER_REAL, &it, NULL);      //设置闹钟
    while (1)
    {
        printf("lai da wo ya!\n");
        sleep(1);
    }
    return 0;
}
