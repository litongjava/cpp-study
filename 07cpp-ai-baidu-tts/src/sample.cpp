/*
 * sample.cpp
 *
 *  Created on: 2019��8��24��
 *      Author: litong
 */
#include "speech.h"
using namespace std;
string app_id = "17076747";
string api_key = "NTzkmkw5NEU0vnISfRgGLwFe";
string secret_key = "PxUPpGvX3O3YNVI2HCtYLwYZ4gqvN6cE";

void tts(aip::Speech client) {
  ofstream ofile;
  string file_ret;
  map<string, string> options;
  //options["spd"] = "9";
  options["per"] = "4"; //度丫丫
  options["aue"] = "4"; //pcm 16k,19bit,1
  ofile.open("./度丫丫-16k.pcm", ios::out | ios::binary);

//  Json::Value result = client.text2audio("how are you", aip::null, file_ret);
  //使用utf-8编码,GBK编码会出现错误
  Json::Value result = client.text2audio("百度语音合成测试", options, file_ret);

  if (!file_ret.empty()) {
    ofile << file_ret;
  }
  cout << "result:" << result << result;
}
int main(int args, char *argv[]) {
  aip::Speech client(app_id, api_key, secret_key);
  tts(client);
}

