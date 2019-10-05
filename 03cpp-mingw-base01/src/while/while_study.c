#include <stdio.h>

int main_while(int argc, char* argv[]) {
  printf("hello,world");
  //while1(); //À¿—≠ª∑
  while2(); //≤ª÷¥––
  return 0;
}

void while1() {
  while (-1) {
    printf("-1");
  }
}

void while2() {
  while (0) {
    printf("0");
  }
}
