#include <iostream>
#include <curl/curl.h>
using namespace std;
int main() {
  const char *dst_url =
      "http://ibotcluster.online.uairobot.com/robot/app/bjhg/ask.action?question=%E4%BD%A0%E5%A5%BD&platform=web";
  //初始curl
  CURL *curl;
  curl = curl_easy_init();

  //初始化curl头部
  struct curl_slist *headers = NULL;
  headers = curl_slist_append(headers, "Accept: Agent-007");

  //设置头部和请求地址
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_URL, dst_url);
    curl_easy_setopt(curl,CURLOPT_HEADER,1);
  }

  //执行请求
  CURLcode response;
  response = curl_easy_perform(curl);

  //释放连接
  if (response != 0) {
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
  }
  //输出返回内容
  cout << response << endl;
  return 0;
}
