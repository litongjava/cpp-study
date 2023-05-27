#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//4.0 控制台打印错误信息, fmt必须是双引号括起来的宏
#define LOG_ERROR(fmt, ...) \
  fprintf(stderr,"[%s:%s:%d][error %d:%s]" fmt "\r\n",__FILE__, __func__, __LINE__, errno, strerror(errno),##__VA_ARGS__)

//4.1 控制台打印错误信息并退出, t同样fmt必须是 ""括起来的字符串常量
#define LOG_ERROR_EXIT(fmt,...) \
  LOG_ERROR(fmt,##__VA_ARGS__),exit(EXIT_FAILURE)

//4.3 if 的 代码检测
#define ERROR_CHECK(code)\
  if((code) < 0) LOG_ERROR_EXIT(#code)

int main() {
  printf("Hello,world\n");
  ERROR_CHECK(1);
  ERROR_CHECK(0);
  LOG_ERROR("%d",-1);
  ERROR_CHECK(-1);
  return 0;
}
