/*
 ============================================================================
 Name        : 02c-base-char-point-strlen-and-sizeof.c
 Author      : litong
 Version     :
 Copyright   : no
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <string.h>

int main(void) {
  char s[] = "\\1234";
  int len = strlen(s);
  int size = sizeof(s);
  printf("%d,%d", len, size);
  return 0;
}
