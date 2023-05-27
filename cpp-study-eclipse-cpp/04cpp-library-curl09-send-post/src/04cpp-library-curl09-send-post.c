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

#include <stdio.h>
#include <string.h>

#define BURSIZE 2048

int hex2dec(char c) {
  if ('0' <= c && c <= '9') {
    return c - '0';
  } else if ('a' <= c && c <= 'f') {
    return c - 'a' + 10;
  } else if ('A' <= c && c <= 'F') {
    return c - 'A' + 10;
  } else {
    return -1;
  }
}

char dec2hex(short int c) {
  if (0 <= c && c <= 9) {
    return c + '0';
  } else if (10 <= c && c <= 15) {
    return c + 'A' - 10;
  } else {
    return -1;
  }
}

//编码一个url
void urlencode(char[] url) {
  int i = 0;
  int len = strlen(url);
  int res_len = 0;
  char res[BURSIZE];
  for (i = 0; i < len; ++i) {
    char c = url[i];
    if (('0' <= c && c <= '9') || ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || c == '/' || c == '.') {
      res[res_len++] = c;
    } else {
      int j = (short int) c;
      if (j < 0)
        j += 256;
      int i1, i0;
      i1 = j / 16;
      i0 = j - i1 * 16;
      res[res_len++] = '%';
      res[res_len++] = dec2hex(i1);
      res[res_len++] = dec2hex(i0);
    }
  }
  res[res_len] = '\0';
  strcpy(url, res);
  return url;
}

// 解码url
void urldecode(char url[]) {
  int i = 0;
  int len = strlen(url);
  int res_len = 0;
  char res[BURSIZE];
  for (i = 0; i < len; ++i) {
    char c = url[i];
    if (c != '%') {
      res[res_len++] = c;
    } else {
      char c1 = url[++i];
      char c0 = url[++i];
      int num = 0;
      num = hex2dec(c1) * 16 + hex2dec(c0);
      res[res_len++] = num;
    }
  }
  res[res_len] = '\0';
  strcpy(url, res);
}
int curl_recv_callback(void *buffer, size_t size, size_t nmemeb) {
  printf("进入回调方法:size_t:%zu memeb:%zu\n", size, nmemeb);
  char *filename = "1.wav";
  FILE* fp = fopen(filename, "a+");
  size_t count = fwrite(buffer, size, nmemeb, fp);
  fclose(fp);
  return count;
}
int main(void) {
  char *base_url = "http://127.0.0.1:10011/bill-tts-server-agent/api/synthesis";
  char *voiceType = "biaobei";
  char *voiceName = urlencode("标准合成_甜美女声_楠楠");
  char *language = "ZH";
  char *text = urlencode("北京合光人工智能机器人技术有限公司");
  char *speed = "5";
  char *volume = "5";
  char *pitch = "5";
  char *audioType = "6";
  char *rate = "1";

  int curl_length = 0;
  curl_length += strlen(base_url);
  char *dest_url = malloc(curl_length + 1);
  strcpy(dest_url, base_url);

  int param_length = 0;
  param_length += strlen("?voiceType=&voiceName=&language=&text=&speed=&volume=&pitch=&audioType=&rate=");
  param_length += strlen(voiceType);
  param_length += strlen(voiceName);
  param_length += strlen(language);
  param_length += strlen(text);
  param_length += strlen(speed);
  param_length += strlen(volume);
  param_length += strlen(pitch);
  param_length += strlen(audioType);
  param_length += strlen(rate);

  char *params = malloc(param_length + 1);
  strcat(params, "voiceType=");
  strcat(params, voiceType);
  strcat(params, "&voiceName=");
  strcat(params, voiceName);
  strcat(params, "&language=");
  strcat(params, language);
  strcat(params, "&text=");
  strcat(params, text);
  strcat(params, "&speed=");
  strcat(params, speed);
  strcat(params, "&volume=");
  strcat(params, volume);
  strcat(params, "&pitch=");
  strcat(params, pitch);
  strcat(params, "&audioType=");
  strcat(params, audioType);
  strcat(params, "&rate=");
  strcat(params, rate);

  printf("%s\n", dest_url);
  printf("%s\n", params);

  CURL* curl = curl_easy_init();
  curl_easy_setopt(curl, CURLOPT_URL, dest_url);
  curl_easy_setopt(curl, CURLOPT_POST, "1");
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, params);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_recv_callback);
  curl_easy_perform(curl);
  curl_easy_cleanup(curl);

  return EXIT_SUCCESS;
}
