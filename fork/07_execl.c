#include <stdio.h>
#include <unistd.h>

int main()
{
    //execl("/bin/ls","ls","-l",NULL);
    execlp("lsx","ls","-l",NULL);
    perror("exec err");
    printf("bye bye");
    return 0;
}
