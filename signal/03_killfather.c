#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

int main()
{
    pid_t pid = fork();
    if (pid > 0)
    {
        //parent
        while (1)
        {
            printf("I am parent,very happy!\n");
            sleep(1);
        }
    }
    else if (pid == 0)
    {
        //son
        sleep(3);
        kill(getppid(), SIGKILL);
    }
    return 0;
}
