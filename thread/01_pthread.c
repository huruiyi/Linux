#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <pthread.h>

void *cal(void *arg)
{
    int i = *((int *)arg);
    printf("Index=%d ,tid=%lu, proId=%d\n", i, pthread_self(), getpid());
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t thread[5];
    ;
    int index[5] = {0, 1, 2, 3, 4};

    for (int i = 0; i < 5; i++)
    {
        pthread_create(&thread[i], NULL, cal, &index[i]);
    }
    sleep(1);
    return 0;
}
