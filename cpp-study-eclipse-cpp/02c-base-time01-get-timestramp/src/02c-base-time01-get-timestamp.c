/*
 ============================================================================
 Name        : 02c-base-time01-get-timestramp.c
 Author      : litong
 Version     :
 Copyright   : no
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(void) {
  time_t time_ptr;
  int timestamp = time(&time_ptr);
  printf("%d\n", timestamp);
  return EXIT_SUCCESS;
}
