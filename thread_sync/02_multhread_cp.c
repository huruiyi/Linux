//作业2，多线程拷贝功能
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define _THR_CNT_   5 //线程数

typedef struct _TaskInfo{
    int num;//线程序号
    void *src;//拷贝原地址
    void *des;//拷贝目标地址
    int size;//拷贝文件总大小
}TaskInfo;

void *thr_cp(void *arg)
{
    TaskInfo *info = arg;
    int num = info->num;
    int cpsize = info->size/_THR_CNT_;
    int mod = info->size % cpsize;

    if(num == _THR_CNT_ - 1){
        //最后一个线程
        memcpy(info->des+num*cpsize,info->src+num*cpsize,cpsize+mod);
    }else{
        memcpy(info->des+num*cpsize,info->src+num*cpsize,cpsize);
    }
    return NULL;
}



int main(int argc,char *argv[])
{
    if(argc != 3){
        printf("./a.out srcfile desfile\n");
        return -1;
    }
    int n = _THR_CNT_;//线程个数
    struct stat sb;
    //获取文件大小
    if(stat(argv[1],&sb) < 0) {
        perror(argv[1]);
        exit(1);
    }
    long lfilesize = sb.st_size;
    //打开原文件和目标文件
    int fdsrc = open(argv[1],O_RDONLY);
    int fddes = open(argv[2],O_RDWR|O_CREAT|O_TRUNC,0666);
    //拓展目标文件
    ftruncate(fddes,lfilesize);

    if(fdsrc <0 || fddes < 0){
        printf("open file %s %s err\n",argv[1],argv[2]);
        exit(1);
    }
    //建立原文的映射区
    void *srcmem = mmap(NULL,lfilesize,PROT_READ,MAP_PRIVATE,fdsrc,0);
    if(srcmem == MAP_FAILED){
        perror("mmap srcfile err");
        exit(1);
    }
    //建立目标的映射区
    void *desmem = mmap(NULL,lfilesize,PROT_READ|PROT_WRITE,MAP_SHARED,fddes,0);
    if(desmem == MAP_FAILED){
        perror("mmap srcfile err");
        exit(1);
    }
    
    TaskInfo taskInfos[_THR_CNT_];
    pthread_t tid[_THR_CNT_];
    int i ;
    for(i = 0 ; i < n ; i ++){
        taskInfos[i].src = srcmem;
        taskInfos[i].des = desmem;
        taskInfos[i].num = i;
        taskInfos[i].size= lfilesize;
        pthread_create(&tid[i],NULL,thr_cp,&taskInfos[i]);
    }
    //回收线程
    for(i = 0; i < n ; i ++){
        pthread_join(tid[i],NULL);
    }
    munmap(srcmem,lfilesize);
    munmap(desmem,lfilesize);
    return 0;
}
