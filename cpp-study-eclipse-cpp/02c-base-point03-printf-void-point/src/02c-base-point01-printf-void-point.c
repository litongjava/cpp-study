/*
 ============================================================================
 Name        : 02c-base-point01-printf-void-point.c
 Author      : litong
 Version     :
 Copyright   : no
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
  //printf char porint
  char *ptr = "litong";
  printf("%s\n", ptr);
  void *ptr2 = "litong";
  char *ptr3 = ptr2;
  printf("%s\n", ptr2);
  printf("%s\n", ptr3);
  printf("%p\n", ptr2);
  return 0;
}
