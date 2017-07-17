#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int fd[2];
    /*
        fd[0]:输入
        fd[1]:输出
    */
    pipe(fd);

    pid_t pid = fork();
    if (pid == 0)
    {
        //son
        sleep(3);
        write(fd[1], "hello\n", 6);
    }
    else if (pid > 0)
    {
        //parent
        char buf[256] = {0};
        int ret = read(fd[0], buf, sizeof(buf));
        if (ret > 0)
        {
            printf("read:%s", buf);
        }
        wait(NULL);
    }
    return 0;
}