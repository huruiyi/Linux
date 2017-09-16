#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/*
 * 管道默认缓冲区是65536
 * 向管道中写入数据时，linux将不保证写入的原子性，管道缓冲区一有空闲区域，写进程就会试图向管道写入数据。当管道满时，读进程不读走管道缓冲区中的数据，那么写操作将一直阻塞。
 * 注意：只有管道的读端存在时，向管道中写入数据才有意义。否则，向管道中写入数据的进程将收到内核传来的SIGPIPE信号，应用程序可以处理该信号，也可以忽略(默认动作则是使应用程序终止)。
 * 当管道数据满时，此时再向管道写数据，写端将阻塞。当读端不存在时，写端写数据，内核将向其发送SIGPIPE信号，默认是终止进程。

*/
int main() {
    int pid;
    int n;
    int fd[2];
    char buf[1000 * 6] = {0};
    if (pipe(fd) < 0) {
        perror("Fail to pipe");
        exit(EXIT_FAILURE);
    }
    if ((pid = fork()) < 0) {
        perror("Fail to fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        close(fd[1]);
        sleep(10);
        close(fd[0]);
        printf("Read port close.\n");
        sleep(3);
    } else {
        close(fd[0]);
        while (1) {
            //sleep(1);
            n = write(fd[1], buf, sizeof(buf));
            printf("Write %d bytes to pipe.\n", n);
        }
    }
    exit(EXIT_SUCCESS);

}

