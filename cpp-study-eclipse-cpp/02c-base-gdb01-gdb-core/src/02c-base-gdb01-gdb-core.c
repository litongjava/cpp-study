#include <stdio.h>

void func() {
  char *p = NULL;
  *p = 3;
}

int main() {
  func();
  return 0;
}
//编译正常,run出现错误
//Segmentation fault (core dumped)
