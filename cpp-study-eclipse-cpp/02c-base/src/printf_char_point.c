/*
 * printf_char_point.c
 *
 *  Created on: 2020年1月9日
 *      Author: litong
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(){
  char *str=malloc(100);;
  strcat(str,"litong");
  printf("%s\n",str);
  return 0;
}


