/*
 ============================================================================
 Name        : 02c-base-point06-point-to-array-each-other.c
 Author      : litong
 Version     :
 Copyright   : no
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_str(char *str) {
  printf("%s\n", str);
  int len = strlen(str);
  for (int i = 0; i < len; i++) {
    char c = str[i];
    printf("%c\n", c);
  }
}
int main(void) {
  char *text = "i-am-chinese";
  char str[100] = "i-am-chinese";
  print_str(text);
  print_str(str);
  char *country[5] = { "Austria", "United States", "United Kingdom", "Switzerland", "Canada" };
  printf("%s\n", country[0]);
  return EXIT_SUCCESS;
}
