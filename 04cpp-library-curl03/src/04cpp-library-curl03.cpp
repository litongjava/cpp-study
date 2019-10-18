//============================================================================
// Name        : 04cpp-library-curl03.cpp
// Author      : litong
// Version     :
// Copyright   : no
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <curl/curl.h>
#include <curl/easy.h>
#include <stddef.h>
#include <iostream>

using namespace std;

int main() {
  CURL *curl = NULL;
  struct curl_slist *headers = NULL;
  curl = curl_easy_init();
  if (curl == NULL) {
    cout << "failed to init curl\n";
    return 0;
  }

  //String¾¡Á¿Ê¹ÓÃconst char *
  const char *dst_url = "http://192.168.99.128:8080/tts-server/api/synthesis";
  //strcat(dst_url,"litong");

  curl_easy_setopt(curl, CURLOPT_URL, dst_url);
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

  CURLcode response;
  response = curl_easy_perform(curl);
  if (response != 0) {
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
  }
  cout << response << endl;
  return 0;
}
