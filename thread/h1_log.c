#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>

/*
1. 实现一个守护进程，每分钟写入一次日志，要求日志文件保存在$HOME/log/下，
	○ 命名规则：程序名.yyyymm   localtime 年份+1900，月份+1
写入内容格式：mm:dd hh:mi:ss 程序名 [进程号]：消息内容 
*/

 
const char *funcName;

void touchfile(int num)
{
    time_t timer  = time(NULL);
    struct tm * ftm = localtime(&timer);
    //printf("Local time is: %s\n", asctime(ftm));
    char strtimebuf[20]={0};
    sprintf(strtimebuf,"%d%02d",ftm->tm_year+1900,ftm->tm_mon+1);
    //printf("%s",strtimebuf);
     
    char *homedir = getenv("HOME");
    char strFileName[256]={0};

    char dirName[256]={0};
    sprintf(dirName,"%s/log/",homedir);
    if (opendir(dirName) == NULL)  
    {   
        extern int errno;
        if(errno==2)
        {
            mkdir(dirName, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        }
        
    }   
    sprintf(strFileName,"%s/log/%s.%s",homedir,funcName,strtimebuf);
    int fd = open(strFileName,O_RDWR|O_CREAT|O_APPEND,0666);
  
    if(fd > 0)
    {
        char slog[100]={0};
        sprintf(slog,"%02d:%02d %02d:%02d:%02d %s [%d]：消息内容 \n",
        ftm->tm_mon, ftm->tm_mday,ftm->tm_hour,ftm->tm_min,ftm->tm_sec,funcName,getpid());
        write(fd,slog,strlen(slog));
        close(fd);
    }
}

int main(int argc,char * argv[])
{
    funcName= argv[0];
    funcName=funcName+2;
    // 1. fork,父进程退出
    pid_t pid = fork();
    if(pid > 0)
    {
        exit(1);
    }
    // 2. setsid
    setsid();
    // 3. chdir
    chdir(getenv("HOME"));
    // 4. umask 
    umask(0002);
    // 5. close 0,1,2
    close(STDIN_FILENO);
    // close(STDOUT_FILENO);
    // close(STDERR_FILENO);
    //核心工作
    struct sigaction act;
    act.sa_flags = 0;
    act.sa_handler = touchfile;
    
    sigemptyset(&act.sa_mask);
    sigaction(SIGALRM,&act,NULL);
    
    struct itimerval it={{3,0},{1,0}};
    setitimer(ITIMER_REAL,&it,NULL);
    while(1)
    {
        printf("XX");
        sleep(1);
    }
    return 0;
}

  