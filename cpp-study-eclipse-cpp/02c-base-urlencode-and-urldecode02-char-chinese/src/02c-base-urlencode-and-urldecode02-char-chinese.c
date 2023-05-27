/*
 ============================================================================
 Name        : 02c-base-urlencode-and-urldecode02-char-chinese.c
 Author      : litong
 Version     :
 Copyright   : no
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//中==>3
//中华==>6
void encode(char text[]) {
  int len = strlen(text);
  printf("len:%d\n",len);
  for (int i = 0; i < len; i++) {
    printf("%c\n",text[i]);
    int n=(short int)text[i];
    printf("%d\n",n);
  }
}
int main(void) {
  puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
  char text[100] = "中华";
  encode(text);
  return EXIT_SUCCESS;
}
