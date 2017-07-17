#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>

void *cal(void *arg)
{
    system("nc 192.168.103.85 8888");
    return NULL;
}

int main(int argc, char *argv[])
{
    int max = 1024;
    pthread_t thread[max];

    for (int i = 0; i < max; i++)
    {
        pthread_create(&thread[i], NULL, cal, NULL);
    }

    for (int i = 0; i < max; i++)
    {
        pthread_join(thread[i], NULL);
    }
    return 0;
}
