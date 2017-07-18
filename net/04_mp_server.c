#include "wrap.h"
#include <signal.h>
#include <sys/wait.h>
#include <ctype.h>

void catchsig(int num)
{
    //使用waitpid
    pid_t wpid;
    while ((wpid = waitpid(-1, NULL, WNOHANG)) > 0)
    {
        printf("wait son pid is %d\n", wpid);
    }
}

int main()
{
    int fd = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(8888);
    serv.sin_addr.s_addr = htonl(INADDR_ANY); //本地任意有效IP都可以作为客户端连接地址

    Bind(fd, (struct sockaddr *)&serv, sizeof(serv));
    Listen(fd, 128);

    sigset_t sbset, oldset;
    sigemptyset(&sbset);
    sigaddset(&sbset, SIGCHLD);              //把SIGCHLD信号加入集合
    sigprocmask(SIG_BLOCK, &sbset, &oldset); //设置阻塞信号集

    struct sockaddr_in client;
    socklen_t len = sizeof(client);
    int flags = 0;
    char strIP[32] = {0};
    int cfd;
    while (1)
    {
        cfd = Accept(fd, (struct sockaddr *)&client, &len);
        printf("new conn %s:%d\n", inet_ntop(AF_INET, &client.sin_addr.s_addr, strIP, sizeof(strIP)), ntohs(client.sin_port));
        if (cfd <= 0)
        {
            continue;
        }
        // 生儿子
        pid_t pid = fork();
        if (pid == 0)
        {
            //子进程 需要去通信
            char buf[256] = {0};
            close(fd);
            while (1)
            {
                int ret = read(cfd, buf, sizeof(buf));
                if (ret < 0)
                {
                    if (errno == EINTR)
                    {
                        continue;
                    }
                    perror("read err");
                    exit(1);
                }
                else if (ret == 0)
                {
                    printf("client closed\n");
                    close(cfd);
                    exit(1);
                }
                else
                {
                    //小写转大写
                    printf("%s", buf);
                    int i;
                    for (i = 0; i < ret; i++)
                    {
                        buf[i] = toupper(buf[i]);
                    }
                    write(cfd, buf, ret); // 写回给客户端
                }
            }
        }
        else if (pid > 0)
        {
            if (flags == 0)
            {
                //解除阻塞
                struct sigaction act;
                act.sa_flags = 0;
                act.sa_handler = catchsig;
                sigemptyset(&act.sa_mask);      //清空临时屏蔽的信号集
                sigaction(SIGCHLD, &act, NULL); //注册捕捉函数

                sigprocmask(SIG_SETMASK, &oldset, NULL); //恢复现场
                flags = 1;
            }
            close(cfd); //为什么关闭？
        }
    }
    return 0;
}
