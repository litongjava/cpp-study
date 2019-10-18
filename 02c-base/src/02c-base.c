#include <stdio.h>
#include <string.h>

int main(void) {
  char src[50], dest[50];
  strcpy(src, "this is source");
  strcpy(dest, "this is dest");
  strcat(dest, src);
  printf("×îÖÕµÄ×Ö·û´®ÊÇ:%s", dest);
}
