#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

int tcp4bind(short port, const char *IP) {
  struct sockaddr_in serv_addr;
  int lfd = socket(AF_INET, SOCK_STREAM, 0);
  bzero(&serv_addr, sizeof(serv_addr)); //地址清0
  if (IP == NULL) {
    //如果这样使用 0.0.0.0,任意ip将可以连接
    serv_addr.sin_addr.s_addr = INADDR_ANY;
  } else {
    if (inet_pton(AF_INET, IP, &serv_addr.sin_addr.s_addr) <= 0) {
      perror(IP); //转换失败
      exit(1);
    }
  }
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port);
  int opt = 1;
  setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
  bind(lfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
  return lfd;
}

int readfromclient(int cfd) {
  char buf[256];
  int ret = read(cfd, buf, sizeof(buf));
  if (ret < 0) {
    if (errno == EAGAIN) {
      return 0;
    }
    perror("read err");
    return -1;
  } else if (ret == 0) {
    printf("client closed\n");
    close(cfd);
  } else {
    write(cfd, buf, ret); //相当于反射
  }
  return 0;
}

int main() {

  int client_cfds[1024];
  int max_client = 0;
  int fd = tcp4bind(8888, NULL);
  int flags = fcntl(fd, F_GETFL);
  flags |= O_NONBLOCK;
  fcntl(fd, F_SETFL, flags); //用于接收连接socket非阻塞
  listen(fd, 128);
  struct sockaddr_in client;
  socklen_t len = sizeof(client);
  while (1) {
    int cfd = accept(fd, (struct sockaddr *)&client, &len);
    if (cfd > 0) {
      //将cfd设置为非阻塞
      int flags = fcntl(cfd, F_GETFL);
      flags |= O_NONBLOCK;
      fcntl(cfd, F_SETFL, flags);
      client_cfds[max_client++] = cfd;
    }
    int i;
    for (i = 0; i < max_client; i++) {
      readfromclient(client_cfds[i]);
    }
    sleep(1);
  }
  return 0;
}
