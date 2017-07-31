//实现大小写转换
#include <arpa/inet.h>
#include <ctype.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  //1. 创建套接字
  int cfd = socket(AF_INET, SOCK_STREAM, 0);
  //2. 连接到服务器端 设置ip和端口，指明连接哪个服务器
  struct sockaddr_in serv;
  serv.sin_port = htons(8889); //设置服务器端口
  serv.sin_family = AF_INET;
  inet_pton(AF_INET, "192.168.137.129", &serv.sin_addr.s_addr); //设置服务器IP

  connect(cfd, (struct sockaddr *)&serv, sizeof(serv));
  //3. 通信 read write
  char buf[256] = {0};
  int ret;
  while (1) {
    //读标准输入
    ret = read(STDIN_FILENO, buf, sizeof(buf));
    if (ret > 0) {
      //写向网络
      write(cfd, buf, ret);
      //从网络读
      ret = read(cfd, buf, sizeof(buf));
      if (ret < 0) {
        perror("read err");
        return -1;
      } else if (ret == 0) {
        //服务器关闭了
        printf("server closed\n");
        break;
      } else {
        write(STDOUT_FILENO, buf, ret); //写到屏幕
      }
    }
  }
  //4. 退出
  close(cfd);
  return 0;
}
