#include <assert.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  char* arg=argv[1];
  assert(arg != NULL);
  int len = strlen(arg);
  char *buf = new char[len + 1];
  snprintf(buf, sizeof(buf), "%s", arg);

  assert(strcmp(arg, "test") != 0);
  puts(buf);

  delete[] buf;
  return 0;
}
