#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void *thr(void *arg)
{
    int i = 0;
    while (i++ < 7)
    {
        printf("I am a thread(%d),tid=%lu\n", i, pthread_self());
        sleep(1);
    }
    //return 0;
}
//主线程挂了，子进程就挂了
//进程中父进程挂了，自己成不受影响
int main()
{
    //  Once a thread has been detached, it can't be joined with pthread_join(3) or be made joinable again.
    pthread_t tid;
    pthread_create(&tid, NULL, thr, NULL);
    //pthread_detach(tid);//线程分离,不等待线程的执行，直接结束

    int ret = pthread_join(tid, NULL); //等待子进程的结束，然后回收, 注意：当设置了pthread_detach的时候不需要再设置pthread_join来回收
    if (ret > 0)
    {
        printf("errno=%d,msg:%s\n", ret, strerror(ret));
    }
    else if (ret == 0)
    {
        printf("thread terminated, tid=%lu", pthread_self());
    }
    return 0;
}