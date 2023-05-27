#include <arpa/inet.h>
#include <asm/byteorder.h>
#include <cygwin/in.h>
#include <cygwin/socket.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/unistd.h>

#define SERVER_PORT 6666
/*
 连接到服务器后，会不停循环，等待输入，
 输入quit后，断开与服务器的连接
 */
int main() {
  //客户端套接字文件描述符
  int client_socket;
  //描述服务器的socket,包含地址类型,IP,端口
  struct sockaddr_in server_addr;
  char sendbuf[1024*1024];
  char recvbuf[1024*1024];
  int date_size;

  //创建socket,返回文件描述符
  if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket");
    return 1;
  }

  //初始化服务端地地址
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(SERVER_PORT);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  //连接服务端口端口获取socket,将获取的socket和client_socket绑定
  if (connect(client_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
    perror("connect");
    return 1;
  }

  printf("连接到主机...\n");
  while (1) {
    printf("发送消息:");
    //读取输入到senbuf
    scanf("%s", sendbuf);
    printf("\n");
    //数据到client端文件描述符
    send(client_socket, sendbuf, strlen(sendbuf), 0);
    if (strcmp(sendbuf, "quit") == 0)
      break;
    printf("读取消息:");
    recvbuf[0] = '\0';
    date_size = recv(client_socket, recvbuf, 1024*1024, 0);
    recvbuf[date_size] = '\0';
    printf("%s\n", recvbuf);
  }
  close(client_socket);
  return 0;
}
