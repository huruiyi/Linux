#include <stdio.h>
#include <unistd.h>

int main()
{
    int ret = 0;
    ret = alarm(5);
    printf("ret=%d\n",ret);
    sleep(3);
    ret=alarm(5);
    printf("ret=%d\n",ret);
    while(1)
    {
        printf("who can kill me?\n");
        sleep(1);
    }
    return 0;
}

