#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

int count = 0;
int filecount(char *dirname)
{
    //1. open dir
    DIR *pDir = opendir(dirname);
    if (pDir == NULL)
    {
        perror("open dir err");
        exit(1);
    }
    //2. read dir
    struct dirent *pdirent = NULL;
    while ((pdirent = readdir(pDir)))
    {
        printf("type:%d,name:%s\n", pdirent->d_type, pdirent->d_name);
        if (pdirent->d_type == DT_DIR)
        {
            //如果是目录类型
            if (strcmp(pdirent->d_name, ".") == 0 || strcmp(pdirent->d_name, "..") == 0)
            {
                continue;
            }
            //需要进入目录统计,需要拼接上级目录，才能进入目录
            char newdirbuf[512] = {0};
            sprintf(newdirbuf, "%s/%s", dirname, pdirent->d_name);
            filecount(newdirbuf);
        }
        if (pdirent->d_type == DT_REG)
        {
            //普通文件类型
            count++;
        }
    }
    //3. close dir
    closedir(pDir);
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("./a.out dir\n");
        return -1;
    }
    filecount(argv[1]);
    printf("count =%d\n", count);
    return 0;
}