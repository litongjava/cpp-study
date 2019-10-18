#include <iostream>
#include <curl/curl.h>
using namespace std;
int main() {
  const char *dst_url =
      "http://ibotcluster.online.uairobot.com/robot/app/bjhg/ask.action?question=%E4%BD%A0%E5%A5%BD&platform=web";
  //��ʼcurl
  CURL *curl;
  curl = curl_easy_init();

  //��ʼ��curlͷ��
  struct curl_slist *headers = NULL;
  headers = curl_slist_append(headers, "Accept: Agent-007");

  //����ͷ���������ַ
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_URL, dst_url);
    curl_easy_setopt(curl,CURLOPT_HEADER,1);
  }

  //ִ������
  CURLcode response;
  response = curl_easy_perform(curl);

  //�ͷ�����
  if (response != 0) {
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
  }
  //�����������
  cout << response << endl;
  return 0;
}
