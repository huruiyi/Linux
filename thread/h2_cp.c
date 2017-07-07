//多线程拷贝
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <pthread.h>

int dstfd,srcfd,n;

struct fileinfo{
    char *psrc;
    char *pdst;
    int cpsize;
    int mod;
};
struct thfileInfoparam
{
    struct fileinfo * info;
    int index;
};

typedef struct fileinfo finfo;
typedef struct thfileInfoparam tcpparam;

void validate(int argc,char *argv[])
{
    n = 5;
    //输入参数至少是3,第4个参数可以是进程个数
    if(argc < 3)
    {
        printf("./a.out src dst [n]\n");
        exit(1);
    }
    if(argc == 4)
    {
        n = atoi(argv[3]);
    }
    //打开源文件
    srcfd = open(argv[1],O_RDONLY);
    if(srcfd < 0)
    {
        perror("open err");
        exit(1);
    }
    //打开目标文件
    dstfd = open(argv[2],O_RDWR|O_CREAT|O_TRUNC,0664);
    if(dstfd < 0)
    {
        perror("open dst err");
        exit(1);
    }
}

void * call(void *agr)
{
    tcpparam * param=(tcpparam *)agr;

     //子进程
    if(param->index== n-1)
    {
      //最后一个子进程
      memcpy(param->info->pdst+param->index*param->info->cpsize,param->info->psrc+param->index*param->info->cpsize,param->info->cpsize+param->info->mod);
    }
    else
    {
      memcpy(param->info->pdst+param->index*param->info->cpsize,param->info->psrc+param->index*param->info->cpsize,param->info->cpsize);
    }

   
    return 0;
}

int main(int argc,char *argv[])
{
    validate(argc,argv);     
    //目标拓展,从原文件获得文件大小,stat
    struct stat sb;
    stat(argv[1],&sb);//为了计算大小
    int len = sb.st_size;
    truncate(argv[2],len);
    //将源文件映射到缓冲区
    char *psrc = mmap(NULL,len,PROT_READ,MAP_PRIVATE,srcfd,0);//PRIVATE可以吗？
    //MAP_PRIVATE 对其他进程不共享
    //MAP_SHARED 对其他进程共享
    if(psrc == MAP_FAILED)
    {
        perror("mmap src err");
        exit(1);
    }
    //将目标文件映射
    char *pdst = mmap(NULL,len,PROT_READ|PROT_WRITE,MAP_SHARED,dstfd,0);
    if(pdst == MAP_FAILED)
    {
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


    finfo * info=(finfo *)malloc(sizeof(finfo));
    info->psrc=psrc;
    info->pdst=pdst;
    info->cpsize=len /n;
    info->mod=len % n;

    pthread_t thread[n]; 
    pthread_t releasethread[n];
    for(int i=0;i<n;i++)
    {
        tcpparam * param=(tcpparam *)malloc(sizeof(tcpparam));
        param->index=i;
        param->info=info;
        pthread_create(&thread[i],NULL,call,param);
        
    }
    for(int i=0;i<n;i++)
    {
        releasethread[i]=pthread_join(thread[i],NULL);
    }
        
    int releaes=1;//成功
    for(int i=0;i<n;i++)
    {
         if(releasethread[i]!=0)
         {
            //失败
            releaes=0;
            break;
         }
       
    }
    if(releaes==0)
    {
        printf("释放失败，复制失败");
    }
    else
    {
         printf("释放成功，复制成功");
    }
    //释放映射区
    if(munmap(psrc,len) < 0)
    {
        perror("munmap src err");
        exit(1);
    }
    if(munmap(pdst,len) < 0)
    {
        perror("munmap dst err");
        exit(1);
    }
    //关闭文件
    close(srcfd);
    close(dstfd);
    return 0;
}

