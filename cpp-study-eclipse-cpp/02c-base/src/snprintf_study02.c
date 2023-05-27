/*
 * snpirntf_sutdy02.c
 *
 *  Created on: 2020年1月9日
 *      Author: litong
 */
#include <stdio.h>
int main() {
  char a[100];
  int i = snprintf(a, 100, "%.*s", 3, "abcd");
  printf("%d a=%s\n", i, a);
  return 0;
}
