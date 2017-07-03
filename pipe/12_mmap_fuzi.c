#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <fcntl.h>

int main()
{
    int fd = open("mem.txt",O_RDWR);

    int *mem = mmap(NULL,4,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if(mem == MAP_FAILED){
        perror("mmap err");
        return -1;
    }

    *mem = 100;
    //fork 
    pid_t pid  = fork();
    if(pid > 0){
        //parent 
        sleep(1);
        printf("I am parent,pid=%d,*mem=%d\n",getpid(),*mem);
        *mem = 102;

    }else if(pid == 0){
        //son 
        printf("I am son,pid=%d,*mem=%d\n",getpid(),*mem);
        *mem = 101;
        sleep(4);
        printf("I am son,pid=%d,*mem=%d\n",getpid(),*mem);
    }


    if(munmap(mem,4) < 0){
        perror("munmap err");
        return -1;
    }
    return 0;
}
