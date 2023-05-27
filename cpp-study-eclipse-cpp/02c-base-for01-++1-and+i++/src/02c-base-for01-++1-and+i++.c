#include <stdio.h>
#include <stdlib.h>

/**
 * 注意观察 i++和++i
 */
int main(void) {
  for (int i = 0; i < 10; i++) {
    printf("%d\n", i);
  }
  for (int i = 0; i < 10; ++i) {
    printf("%d\n", i);
  }
  return EXIT_SUCCESS;
}
