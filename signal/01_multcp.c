//多进程拷贝
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int argc,char *argv[])
{
    int n = 5;
    //输入参数至少是3,第4个参数可以是进程个数
    if(argc < 3){
        printf("./a.out src dst [n]\n");
        return 0;
    }
    if(argc == 4){
        n = atoi(argv[3]);
    }
    //打开源文件
    int srcfd = open(argv[1],O_RDONLY);
    if(srcfd < 0){
        perror("open err");
        exit(1);
    }
    //打开目标文件
    int dstfd = open(argv[2],O_RDWR|O_CREAT|O_TRUNC,0664);
    if(dstfd < 0){
        perror("open dst err");
        exit(1);
    }
    //目标拓展,从原文件获得文件大小,stat
    struct stat sb;
    stat(argv[1],&sb);//为了计算大小
    int len = sb.st_size;
    truncate(argv[2],len);
    //将源文件映射到缓冲区
    char *psrc = mmap(NULL,len,PROT_READ,MAP_PRIVATE,srcfd,0);//PRIVATE可以吗？
    if(psrc == MAP_FAILED){
        perror("mmap src err");
        exit(1);
    }
    //将目标文件映射
    char *pdst = mmap(NULL,len,PROT_READ|PROT_WRITE,MAP_SHARED,dstfd,0);
    if(pdst == MAP_FAILED){
        perror("mmap dst err");
        exit(1);
    }
    //创建多个子进程
    int i =0;
    for(i = 0; i < n; i ++)
    {
        if(fork() == 0)
            break;
    }
    //计算子进程需要拷贝的起点和大小
    int cpsize = len /n;
    int mod    = len % n;
    //数据拷贝,memcpy 
    if(i < n){//子进程
        if(i == n-1){//最后一个子进程
            
            memcpy(pdst+i*cpsize,psrc+i*cpsize,cpsize+mod);
        }
        else
        {
            memcpy(pdst+i*cpsize,psrc+i*cpsize,cpsize);
        }
    }
    else
    {
        for(i = 0; i < n ; i ++)
        {
            wait(NULL);
        }
    }
    //释放映射区
    if(munmap(psrc,len) < 0){
        perror("munmap src err");
        exit(1);
    }
    if(munmap(pdst,len) < 0){
        perror("munmap dst err");
        exit(1);
    }
    //关闭文件
    close(srcfd);
    close(dstfd);
    return 0;
}

