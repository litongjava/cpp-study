/*
 ============================================================================
 Name        : 02c-base-if-check.c
 Author      : litong
 Version     :
 Copyright   : no
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define LOG_ERROR_EXIT(fmt,...)\
  printf(fmt) \
  printf(##)


#define IF_CHECK(code)\
  if(code<0) LOG_ERROR_EXIT(#code);

int main(void) {
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	IF_CHECK(-1);
	return EXIT_SUCCESS;
}
