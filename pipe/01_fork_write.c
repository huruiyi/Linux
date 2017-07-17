#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("./a.out filename\n");
        return -1;
    }
    int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd < 0)
    {
        perror("open err");
        exit(1);
    }
    pid_t pid = fork();
    if (pid == 0)
    {
        //son
        write(fd, "hello\n", 6);
    }
    else if (pid > 0)
    {
        //parent
        sleep(1);
        write(fd, "world\n", 6);
        wait(NULL);
    }
    close(fd);
    return 0;
}