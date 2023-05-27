/*
 ============================================================================
 Name        : c-base-point-demo02.c
 Author      : litong
 Version     :
 Copyright   : no
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int len=1024;
	char buf[len];
	char *p=buf;
	int ret=p-buf;
	printf("%d\n",ret);
	return EXIT_SUCCESS;
}
