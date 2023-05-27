#include <bits/types/FILE.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include <curl/typecheck-gcc.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp);
int call_url(char *url);

int main(int argc, char **argv) {
  if (argv[1] == NULL) {
    printf("usage:%s url\n", argv[0]);
    exit(1);
  }
  call_url(argv[1]);
  return 0;
}

size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp) {
  FILE *fp;
  int total;
  fp = fopen("./index", "w+");
  if (fp == NULL) {
    printf("cannot open txt.index\n");
    return -2;
  }
  //开始写
  total = fwrite(buffer, size, nmemb, fp);
  //写完
  fclose(fp);
  return total;
}

int call_url(char *url) {
  // 初始化libcurl
  CURLcode return_code;

  return_code = curl_global_init(CURL_GLOBAL_ALL);
  if (CURLE_OK != return_code) {
    printf("init libcurl failed.");
    return -1;
  }

  CURL *curl = curl_easy_init();
  if (NULL == curl) {
    printf("get a easy handle failed.");
    curl_global_cleanup();
    return -1;
  }

  //curl_easy_setopt(easy_handle,CURLOPT_URL,"www.baidu.com");
  curl_easy_setopt(curl, CURLOPT_URL, url); //
  //回调函数
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);  //
  //如果你没有通过CURLOPT_WRITEFUNCTION属性给easy handle设置回调函数
  //libcurl会提供一个默认的回调函数，它只是简单的将接收到的数据打印到标准输出。
  //你也可以通过CURLOPT_WRITEDATA属性给默认回调函数传递一个已经打开的文件指针，

  //执行请求
  curl_easy_perform(curl);
  curl_easy_cleanup(curl);
  curl_global_cleanup();
}

