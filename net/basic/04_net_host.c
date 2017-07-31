#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

int main() {
  struct sockaddr_in serv;
  //网络字节序和本地(主机)字节序转化
  serv.sin_port = htons(8888);
  serv.sin_family = AF_INET; //版本
  serv.sin_addr.s_addr = INADDR_ANY;

  int ref = inet_pton(AF_INET, "192.168.126.128", &serv.sin_addr.s_addr);
  if (ref > 0) {
    printf("主机字节序===>网络字节序(inet_pton)%ul\n", serv.sin_addr.s_addr);
  } else {
    printf("主机字节序===>网络字节序失败\n");
  }

  char chIp[16] = {0};
  const char *ip = inet_ntop(AF_INET, &serv.sin_addr.s_addr, chIp, sizeof(chIp));
  if (ip != NULL) {
    printf("网络字节序===>主机字节序(inet_ntop)%s\n", chIp);
  } else {
    printf("网络字节序===>主机字节序失败\n");
  }

  printf("网络字节序IP:%u\n", serv.sin_addr.s_addr);
  printf("网络字节序Port:%u\n", serv.sin_port);

  // - 端口间转化,Port16位
  // uint16_t htons(uint16_t hostshort);//转Port：16位
  // uint16_t ntohs(uint16_t netshort);

  unsigned short netshort = htons(8888);
  printf("网络字节序===>主机字节序： 端口转化%d,%d\n", ntohs(serv.sin_port), ntohs(netshort));
  printf("主机字节序===> 网络字节序：端口转化%d\n", netshort);

  // - 地址间转化,IP:32位
  // uint32_t htonl(uint32_t hostlong);
  // uint32_t ntohl(uint32_t netlong);

  uint32_t hostlong = ntohl(serv.sin_addr.s_addr);
  uint32_t netlong = htonl(hostlong);
  uint32_t netlong2 = htonl(INADDR_ANY);

  printf("网络字节序===>主机字节序： 端口转化%u,%u\n", ntohl(netlong), ntohl(serv.sin_addr.s_addr));
  printf("主机字节序===> 网络字节序：端口转化%u\n", netlong);

  return 0;
}