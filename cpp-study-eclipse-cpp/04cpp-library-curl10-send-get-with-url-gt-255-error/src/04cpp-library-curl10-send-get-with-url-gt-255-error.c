/*
 ============================================================================
 Name        : 04cpp-library-curl10-send-get-with-url-gt-255-error.c
 Author      : litong
 Version     :
 Copyright   : no
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

int main(void) {
  char *dest_url =
      "http://127.0.0.1:10011/bill-tts-server-agent/api/synthesis?voiceType=biaobei&voiceName=标准合成_甜美女声_楠楠&language=ZH&text=北京合光人工智能机器人技术有限公司&speed=5&volume=5&pitch=5&audioType=6&rate=1";
  printf("%s\n",dest_url);
  CURL* curl = curl_easy_init();
  curl_easy_setopt(curl, CURLOPT_URL, dest_url);
  curl_easy_perform(curl);
  curl_easy_cleanup(curl);
  return EXIT_SUCCESS;
}
