#include <arpa/inet.h>
#include <asm/byteorder.h>
#include <cygwin/in.h>
#include <cygwin/socket.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/unistd.h>

#define SERVER_PORT 6666
/*
 监听后，一直处于accept阻塞状态，
 直到有客户端连接，
 当客户端如数quit后，断开与客户端的连接
 */
int main() {
  //调用socket返回的文件描述符
  int server_socket;
  //调用accpet返回的文件描述符
  int client_socket;
  //声明两个套接字sockaddr_in结构体变量，分别表示客户端和服务器
  struct sockaddr_in server_addr;
  struct sockaddr_in client_addr;
  int addr_len = sizeof(client_addr);

  char buffer[1024*1024];
  int data_size;

  //创建socket,返回文件描述符
  if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket");
    return 1;
  }

  //清空server_addr
  bzero(&server_addr, sizeof(server_addr));
  //初始化服务器端的套接字，并用htons和htonl将端口和地址转成网络字节序
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(SERVER_PORT);
  //ip可是是本服务器的ip，也可以用宏INADDR_ANY代替，代表0.0.0.0，表明所有地址
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  //将socket文件描述符和socket绑定
  if (bind(server_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
    perror("bind");
    return 1;
  }

  //设置服务器上的socket为监听状态
  if (listen(server_socket, 5) < 0) {
    perror("listen");
    return 1;
  }
  while (1) {
    printf("监听端口: %d\n", SERVER_PORT);
    //接受发送到server_socket中的清求,将请求方的ip和端口写入到client_addr,并返回接受数据的文件描述符
    client_socket = accept(server_socket, (struct sockaddr*) &client_addr, (socklen_t*) &addr_len);
    if (client_socket < 0) {
      perror("accept");
      continue;
    }
    printf("等待消息...\n");

    printf("peer ip   : %s\n", inet_ntoa(client_addr.sin_addr));
    printf("peer port : %d\n", htons(client_addr.sin_port));
    while (1) {
      printf("读取消息:");
      buffer[0] = '\0';
      data_size = recv(client_socket, buffer, 1024*1024, 0);
      if (data_size < 0) {
        perror("recv null");
        continue;
      }
      buffer[data_size] = '\0';
      if (strcmp(buffer, "quit") == 0)
        break;
      printf("%s\n", buffer);

      printf("发送消息:");
      scanf("%s", buffer);
      printf("\n");
      send(client_socket, buffer, strlen(buffer), 0);
      if (strcmp(buffer, "quit") == 0)
        break;
    }
  }
  close(server_socket);
  return 0;
}
