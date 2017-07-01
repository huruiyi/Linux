#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int fd = fcntl(STDOUT_FILENO,F_DUPFD,0);

    write(fd,"hello\n",6);
    return 0;
}

