#include <stdio.h>

int main(void) {
  char s[] = { "language" }, *p = s, *q;
  q = p + 1;
  printf("%s\n", q);
}
