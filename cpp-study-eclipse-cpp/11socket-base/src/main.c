/*
 * main.c
 *
 *  Created on: 2019年11月11日
 *      Author: litong
 */

#include <arpa/inet.h>
#include <cygwin/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
  struct in_addr addr1;
  ulong l1 = inet_addr("192.168.0.74");
  //赋值变量的内容地址
  memcpy(&addr1, &l1, 4);
  //转成成点分十进制输出
  printf("%s\n", inet_ntoa(addr1));
  return 0;
}
