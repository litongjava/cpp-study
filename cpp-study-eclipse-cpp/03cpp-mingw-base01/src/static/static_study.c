#include <stdio.h>

/*函数声明*/
void func1(void);
//全局变量
int count = 10;
int main_static(int argc, char* argv[]) {
  while (0) {
    func1();
  }
  return 0;
}

void func1(void) {
  static int thingy = 5;
  thingy++;
  printf("thingy %d,count %d \n", thingy, count);
}
