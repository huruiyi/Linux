#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>

void show_hello(int num)
{
    printf("hello,world\n");
}

int main()
{
    struct sigaction act;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    act.sa_handler = show_hello;
    sigaction(SIGALRM,&act,NULL);
    struct itimerval it={{1,0},{1,0}};
    setitimer(ITIMER_REAL,&it,NULL);
    while(1)
    {
        sleep(2);
    }
    return 0;
}

