/*
 ============================================================================
 Name        : 04cpp_library_curl05_curl_easy_getinfo.c
 Author      : litong
 Version     :
 Copyright   : no
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
/**
 * 获取response http code和 response content_type
 */

#include <curl/curl.h>
#include <curl/easy.h>
#include <curl/typecheck-gcc.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  char * dest_url = "http://www.baidu.com";
  CURL* curl = curl_easy_init();
  curl_easy_setopt(curl, CURLOPT_URL, dest_url);
  CURLcode response = curl_easy_perform(curl);
  long http_code;
  char *content_type = NULL;
  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
  curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &content_type);
  printf("%ld %s %d\n", http_code, content_type, response);
  curl_easy_cleanup(curl);
  return EXIT_SUCCESS;
}
