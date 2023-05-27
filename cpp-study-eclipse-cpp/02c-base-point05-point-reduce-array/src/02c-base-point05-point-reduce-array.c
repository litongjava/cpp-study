/*
 ============================================================================
 Name        : 02c-base-point05-point-reduce-array.c
 Author      : litong
 Version     :
 Copyright   : no
 Description : 数组指针减数组
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int len = 1024;
  char buf[len];
  char *tp = buf;
  int result = tp - buf;
  printf("result %d\n", result);
  *tp++;
  result=tp-buf;
  printf("result %d\n",result);
  return EXIT_SUCCESS;
}
