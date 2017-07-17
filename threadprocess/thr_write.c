#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

pthread_mutex_t mutex;

char buf[20];

void *thr1(void *arg)
{
    int i = 0;
    for (; i < 20; i++)
    {
        usleep(rand() % 3);
        buf[i] = '0';
    }
    return NULL;
}

void *thr2(void *arg)
{
    int i = 0;
    for (; i < 20; i++)
    {
        usleep(rand() % 3);
        buf[i] = '1';
    }
    return NULL;
}

int main()
{
    memset(buf, 0x00, sizeof(buf));
    pthread_t tid[2];
    pthread_create(&tid[0], NULL, thr1, NULL);
    pthread_create(&tid[1], NULL, thr2, NULL);

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    printf("buf is %s\n", buf);
    return 0;
}
