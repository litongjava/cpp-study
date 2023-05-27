#include <stdio.h>

int main(int argc, char* argv[]) {
  //Êä³öargc
  printf("argc:%d \n", argc);
  //Êä³öargv
  for (int i = 0; i < argc; i++) {
    char* buf = argv[i];
    printf("%d:%s \n", i, buf);
  }
  return 0;
}
