#include <iostream>
#include <ctime>
using namespace std;
int main_date(int argc,char* argv[]){
  //基于当前系统的日期时间,返回时间戳
  time_t now=time(0);
  cout << "now:"<<now<<endl;
  //将now转为字符串形式
  char* dt=ctime(&now);
  cout <<"dt:"<<dt<<endl;
  //将now转为tm结构
  tm* gmtm=gmtime(&now);
  cout <<"gmtm:"<<gmtm<<endl;
  //转为utc时间
  dt=asctime(gmtm);
  cout <<"utc时间:"<<dt<<endl;
  return 0;
}
