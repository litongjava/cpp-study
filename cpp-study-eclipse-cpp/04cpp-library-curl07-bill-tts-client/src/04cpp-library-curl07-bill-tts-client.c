/*
 ============================================================================
 Name        : 04cpp-library-curl07-bill-tts-client.c
 Author      : litong
 Version     :
 Copyright   : no
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <bits/types/FILE.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include <curl/typecheck-gcc.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int curl_recv_callback(void *buffer, size_t size, size_t nmemeb) {
  printf("进入回调方法:size_t:%zu memeb:%zu\n", size, nmemeb);
  char *filename="1.wav";
  FILE* fp = fopen(filename, "a+");
  size_t count = fwrite(buffer, size, nmemeb, fp);
  fclose(fp);
  return count;
}
int main(void) {
  char *base_url = "http://127.0.0.1:10011/bill-tts-server-agent/api/synthesis";
  char *voiceType = "biaobei";
  char *voiceName = "标准合成_甜美女声_楠楠";
  char *language = "ZH";
  char *text = "北京合光人工智能机器人技术有限公司";
  char *speed = "5";
  char *volume = "5";
  char *pitch = "5";
  char *audioType = "6";
  char *rate = "1";

  int curl_length = 0;
  curl_length += strlen(base_url);
  curl_length += strlen("?voiceType=&voiceName=&language=&text=&speed=&volume=&pitch=&audioType=&rate=");
  curl_length += strlen(voiceType);
  curl_length += strlen(voiceName);
  curl_length += strlen(language);
  curl_length += strlen(text);
  curl_length += strlen(speed);
  curl_length += strlen(volume);
  curl_length += strlen(pitch);
  curl_length += strlen(audioType);
  curl_length += strlen(rate);

  char *dest_url = malloc(curl_length+1);
  strcat(dest_url, base_url);
  strcat(dest_url, "?voiceType=");
  strcat(dest_url, voiceType);
  strcat(dest_url, "&voiceName=");
  strcat(dest_url, voiceName);
  strcat(dest_url, "&language=");
  strcat(dest_url, language);
  strcat(dest_url, "&text=");
  strcat(dest_url, text);
  strcat(dest_url, "&speed=");
  strcat(dest_url, speed);
  strcat(dest_url, "&volume=");
  strcat(dest_url, volume);
  strcat(dest_url, "&pitch=");
  strcat(dest_url, pitch);
  strcat(dest_url, "&audioType=");
  strcat(dest_url, audioType);
  strcat(dest_url, "&rate=");
  strcat(dest_url, rate);
  printf("%s\n", dest_url);
  CURL* curl = curl_easy_init();
  curl_easy_setopt(curl, CURLOPT_URL, dest_url);
  curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,curl_recv_callback);
  curl_easy_perform(curl);
  curl_easy_cleanup(curl);
  return EXIT_SUCCESS;
}
