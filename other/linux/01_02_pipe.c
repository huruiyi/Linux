#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int fd[2];
    
    int pret=pipe(fd);
    if(pret<0)
    {
        perror("fail to create pipe\n");
        exit(EXIT_FAILURE);
    }

    int fret=fork();
    if(fret>0)
    {
        printf("father\n");
        //father write
        close(fd[0]);
        int ret = write(fd[1],"Hello",6);
        printf("father:;write %d size\n",ret);
    } 
    else if(fret==0)
    {
        printf("son\n");
        //sleep(1);
        //son read
        close(fd[1]);
        char buf[20]={0};
        read(fd[0],buf,sizeof(buf));
        printf("son::read:%s\n",buf); 
    }
    else
    {
        perror("error\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}
