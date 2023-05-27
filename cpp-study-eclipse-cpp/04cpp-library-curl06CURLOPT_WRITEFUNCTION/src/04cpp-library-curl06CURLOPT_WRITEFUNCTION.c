/*
 ============================================================================
 Name        : 04cpp-library-curl06CURLOPT_WRITEFUNCTION.c
 Author      : litong
 Version     :
 Copyright   : no
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

/**
 * sutdy CURLOPT_WRITEFUNCTION
 */
int curl_recv_callback(void *buffer, size_t size, size_t memeb) {
  printf("进入回调方法:size_t:%zu memeb:%zu\n", size, memeb);
  char *response_content = buffer;
  printf("%s", response_content);
  return 0;
}
int main(void) {
  char *dest_url = "http://www.baidu.com";
  CURL *curl = curl_easy_init();
  curl_easy_setopt(curl, CURLOPT_URL, dest_url);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_recv_callback);
  CURLcode response = curl_easy_perform(curl);
  printf("response:%d\n", response);
  curl_easy_cleanup(curl);
  return EXIT_SUCCESS;
}

