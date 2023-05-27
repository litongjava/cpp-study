#include <iostream>
#include <fstream>
using namespace std;
int main_stream(int argc, char* argv[]) {
  char data[100];
  //以写模式打开文件
  ofstream outfile;
  outfile.open("afile.data");
  //从命令行中获取数据
  cout << "input your name:" << endl;
  cin.getline(data, 100);
  //向文件中写入数据
  outfile << data << endl;

  //再次获取用户输入,向文件中写入数据
  cout << "input your age" << endl;
  cin.getline(data, 100);
  outfile << data << endl;
  //关闭文件
  outfile.close();

  //以读模式打开文件
  ifstream infile;
  infile.open("afile.data");
  //读取文件中的内容
  infile >> data;
  //输出内容
  cout << data << endl;
  //再次读取并输出
  infile >> data;
  cout << data << endl;
  //关闭文件
  infile.close();
  return 0;
}
