#include <string.h>
#include <stdio.h>
int main() {
  char *api_base = "http://127.0.0.1:10010/tts-server";
  size_t url_len= strlen(api_base);
  printf("%zu\n",url_len);
  return 0;
}
