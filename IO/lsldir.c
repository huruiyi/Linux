#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

int count = 0;
int filecount(char *dirname)
{
    DIR *pDir = opendir(dirname);
    if (pDir == NULL) 
    {
        perror("open dir err");
        exit(1);
    }
    struct dirent* pdirent = NULL;
    while ((pdirent = readdir(pDir))) 
    {
        //-rwxrw-rw- 1 itheima itheima  433 6月  30 18:34 01_open_max.c*
        struct stat sb;
        int ret = lstat(pdirent->d_name,&sb);
        char fmode[11]={0};
        //搞定文件类型
        if(S_ISREG(sb.st_mode)) fmode[0]='-'; 
        if(S_ISDIR(sb.st_mode)) fmode[0]='d'; 
        if(S_ISCHR(sb.st_mode)) fmode[0]='c'; 
        if(S_ISBLK(sb.st_mode)) fmode[0]='b'; 
        if(S_ISFIFO(sb.st_mode)) fmode[0]='p'; 
        if(S_ISLNK(sb.st_mode)) fmode[0]='l'; 
        if(S_ISSOCK(sb.st_mode)) fmode[0]='s'; 

        //搞定用户权限
        fmode[1]=(S_IRUSR&sb.st_mode)?'r':'-';
        fmode[2]=(S_IWUSR&sb.st_mode)?'w':'-';
        fmode[3]=(S_IXUSR&sb.st_mode)?'x':'-';

        fmode[4]=(S_IRGRP&sb.st_mode)?'r':'-';
        fmode[5]=(S_IWGRP&sb.st_mode)?'w':'-';
        fmode[6]=(S_IXGRP&sb.st_mode)?'x':'-';

        fmode[7]=(S_IROTH&sb.st_mode)?'r':'-';
        fmode[8]=(S_IWOTH&sb.st_mode)?'w':'-';
        fmode[9]=(S_IXOTH&sb.st_mode)?'x':'-';

        if (pdirent->d_type != DT_DIR) 
        {
            struct tm * ftm = localtime(&sb.st_mtim.tv_sec);
            char strtimebuf[20]={0};
            sprintf(strtimebuf,"%d月  %d %02d:%02d",ftm->tm_mon+1,ftm->tm_mday,ftm->tm_hour,ftm->tm_min);
            printf("%s %ld %s %s %ld %s %s\n",fmode,sb.st_nlink,getpwuid(sb.st_uid)->pw_name,getgrgid(sb.st_gid)->gr_name,sb.st_size,strtimebuf,pdirent->d_name); 
        }
        
        ///printf("type:%d,name:%s\n", pdirent->d_type, pdirent->d_name);
        if (pdirent->d_type == DT_DIR) 
        {           
            if (strcmp(pdirent->d_name, ".") == 0 || strcmp(pdirent->d_name, "..") == 0) {
                continue;
            }           
            char newdirbuf[512] = { 0 };
            sprintf(newdirbuf, "%s/%s", dirname, pdirent->d_name);
            filecount(newdirbuf);
        }
        if (pdirent->d_type == DT_REG) 
        {
            count++;
        }
    }   
    closedir(pDir);
}
                            
int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("./a.out dir\n");
        return -1;
    }
    filecount(argv[1]);
    printf("count =%d\n", count);
    return 0;
}
