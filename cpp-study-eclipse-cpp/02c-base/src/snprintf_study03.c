/*
 * snprintf_study03.c
 *
 *  Created on: 2020年1月9日
 *      Author: litong
 */
#include<stdio.h>
#include<stdlib.h>
int main() {
  char str[10] = { 0 };
  int nLen = snprintf(str, sizeof(str), "123456789012345678");
  printf("%d str=%s\n", nLen, str);
  return 0;
}

