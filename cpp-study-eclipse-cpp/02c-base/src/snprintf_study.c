/*
 * snprintf_study.c
 *
 *  Created on: 2020年1月9日
 *      Author: litong
 */
#include <stdio.h>
int main() {
  char a[100];
  int i = snprintf(a, 13, "%013d", 123456);
  printf("%d a=%s\n", i, a);
  i = snprintf(a, 9, "%012d", 123456);
  printf("%d a=%s\n", i, a);
  return 0;
}

