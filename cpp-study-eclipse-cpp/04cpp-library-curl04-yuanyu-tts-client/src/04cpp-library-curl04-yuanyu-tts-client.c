/*
 ============================================================================
 Name        : 04cpp-library-curl04-yuanyu-tts-client.c
 Author      : litong
 Version     :
 Copyright   : no
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <curl/curl.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int wave_recv_callback(void *buffer, size_t size, size_t memeb, void *ptr);
int main(void) {
  puts("!!!04cpp-library-curl04-yuanyu-tts-client!!!"); /* prints !!!Hello World!!! */

  char *api_base = "http://127.0.0.1:10010/bill_tts-server";
  char *api_uri = "/api/synthesis";
  char *voice_type = "biaobei";
  char *voice_name = "甜美女生_楠楠燕";
  char *text = "北京合光人工智能机器人技术有限公司";
  char *audio_type = "wav";

  char *params_str = "?voiceType=&voiceName=&text=&audioType=";

  size_t url_len = strlen(params_str);
  url_len += strlen(api_base);
  url_len += strlen(api_uri);
  url_len += strlen(voice_type);
  url_len += strlen(voice_name);
  url_len += strlen(text);
  url_len += strlen(audio_type);

  char *dest_url = malloc(url_len);

  strcat(dest_url, api_base);
  strcat(dest_url, api_uri);
  strcat(dest_url, "?voiceType=");
  strcat(dest_url, voice_type);
  strcat(dest_url, "&voiceName=");
  strcat(dest_url, voice_name);
  strcat(dest_url, "&text=");
  strcat(dest_url, text);
  strcat(dest_url, "&audioType=");
  strcat(dest_url, audio_type);

  printf("url:%s\n", dest_url);
  CURL* curl = curl_easy_init();
  if (curl == NULL) {
    printf("curl_easy_init() fail\n");
    curl_global_cleanup();
    return -1;
  }
  curl_easy_setopt(curl, CURLOPT_URL, dest_url);
  curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
  curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, 15000);
  curl_easy_setopt(curl, CURLOPT_DNS_CACHE_TIMEOUT, 36000);

  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, wave_recv_callback);

  char buffer[128] = { 0 };
  size_t buffer_size = sizeof(buffer);
  struct curl_slist *headers=NULL;
  snprintf(buffer,buffer_size,"Content-Type:application/json");
  headers=curl_slist_append(headers,buffer);
  snprintf(buffer,buffer_size,"User-Agent:freeswitch");
  headers=curl_slist_append(headers,buffer);

  curl_easy_setopt(curl,CURLOPT_HTTPHEADER,headers);

  curl_easy_perform(curl);
  long http_code;
  char *content_type;
  curl_easy_getinfo(curl,CURLINFO_RESPONSE_CODE,&http_code);
  curl_easy_getinfo(curl,CURLINFO_CONTENT_TYPE,content_type);
  curl_slist_free_all(headers);
  pritnf("http_code:%l,content_type:%s\n",http_code,content_type);
  printf("执行完成\n");
  return EXIT_SUCCESS;
}

static int wave_recv_callback(void *buffer, size_t size, size_t memeb, void *ptr){

}
