/*
 * c-base-point.c
 *
 *  Created on: 2019年12月25日
 *      Author: litong
 */
#include <stdio.h>
int main(){
  int i=10;
  void *v=&i;
  int *p=v;
  int i3=*p;
  printf("%d",i3);
  return 1;
}

