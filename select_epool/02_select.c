#include "wrap.h"
#include <sys/select.h>

int main() {
  int sockfd = Socket(AF_INET, SOCK_STREAM, 0); //套接字
  struct sockaddr_in serv;
  bzero(&serv, sizeof(serv));
  serv.sin_family = AF_INET;
  serv.sin_port = htons(8888);
  //inet_pton(AF_INET,"192.168.103.87",&serv.sin_addr.s_addr);//ip地址转换
  serv.sin_addr.s_addr = htonl(INADDR_ANY);

  int opt = 1;
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)); //端口复用
  Bind(sockfd, (struct sockaddr *)&serv, sizeof(serv));

  Listen(sockfd, 128);

  //定义select使用的集合
  fd_set rdfds, allfds;   //allfds 是备份使用
  FD_ZERO(&rdfds);        //清0
  FD_SET(sockfd, &rdfds); //将sockfd加入集合中
  int nfds = sockfd;

  allfds = rdfds;
  while (1) {
    rdfds = allfds;                                         //后面需要维护好allfds
    int nread = select(nfds + 1, &rdfds, NULL, NULL, NULL); //阻塞等待事件就绪
    //接下来处理就绪事件
    if (nread <= 0) {
      continue;
    }
    int i = 0;
    for (i = sockfd; i < nfds + 1; i++) {
      if (FD_ISSET(i, &rdfds)) {
        //说明该文件描述符需要处理
        if (i == sockfd) {
          //此时需要accept
          struct sockaddr_in client;
          socklen_t len = sizeof(client);
          int cfd = Accept(i, (struct sockaddr *)&client, &len); //是否会阻塞？不会
          //需要将cfd加入到集合中，继续select
          if (cfd > 0) {
            FD_SET(cfd, &allfds); //将新的连接加入到集合中
            //nfds 值也需要修改 cfd 未必是最大的描述符
            if (nfds < cfd)
              nfds = cfd;
          }
        } else {
          //处理客户端的读事件
          char buf[256] = {0};
          int ret = Read(i, buf, sizeof(buf));
          if (ret < 0) {
            perror("read err");
            close(i);
            FD_CLR(i, &allfds); //清除出集合
          } else if (ret == 0) {
            printf("client closed\n");
            close(i);
            FD_CLR(i, &allfds);
          } else {
            write(i, buf, ret); //反射
          }
        }
        //需要判断nread是否用完了
        if (nread-- <= 0) {
          break; //此时代表就绪事件已经处理完毕，不用再循环了
        }
      }
    }
  }
  return 0;
}