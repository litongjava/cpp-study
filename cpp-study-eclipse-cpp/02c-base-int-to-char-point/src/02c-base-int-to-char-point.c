/*
 ============================================================================
 Name        : 02c-base-int-to-char-point.c
 Author      : litong
 Version     :
 Copyright   : no
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int rate = 8000;
  char* str=malloc(10);
  sprintf(str, "%d", rate);
  printf("str:%s\n", str);
  return EXIT_SUCCESS;
}

