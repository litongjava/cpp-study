/*
 ============================================================================
 Name        : 02c-base-point04-not-point.c
 Author      : litong
 Version     :
 Copyright   : no
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <bits/stdint-uintn.h>

int main(void) {
  puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
  uint16_t port = 0;
  uint16_t *ptr_port = &port;
  if (ptr_port) {
    printf("ptr_port\n");
  }

  uint16_t *othre_ptr = NULL;
  if(othre_ptr){
    printf("other_prt\n");
  }
  return EXIT_SUCCESS;
}
