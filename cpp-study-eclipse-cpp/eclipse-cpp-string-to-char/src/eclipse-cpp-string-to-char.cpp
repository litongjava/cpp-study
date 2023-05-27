//============================================================================
// Name        : eclipse-cpp-string-to-char.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#pragma warning(disable:4996)
#include<iostream>
#include<string>
using namespace std;

int main() {
  string str;
  str = "world";

  char y[20];
  //目标,数量,起始位置
  str.copy(y, 5, 0);
  //移动指针,并设置结束符
  *(y + 5) = '\0';

  cout << "str前5个元素的值值为：" << y << endl;

  return 0;
}

/**
 * 使用data()方法将string转为char*
 */
//#include<iostream>
//#include<string>
//using namespace std;
//int main() {
//  string str;
//  str = "hello world";
//  //这里一定定义为const char *格式,char * p = (char*)str.data()
//  const char *y = str.data();
//
//  cout << "str的值为：" << y << endl;
//
//  return 0;
//}
/**
 * 使用c_str()方法,将string转为char*
 */
//#include<iostream>
//#include<string>
//using namespace std;
//int main() {
//  string str;
//  str = "hello world";
//
//  //这里一定定义为const char *格式，char * p = (char*)str.data()
//  const char *y = str.c_str();
//  cout << "str的值为：" << y << endl;
//
//  return 0;
//}
/**
 * char[],char* 转String
 */
//#include <iostream>
//#include <string>
//
//using namespace std;
//int main() {
//  string str;
//  char x[] = "hello";
//  char *y = "Hello";
//  str = x;
//  cout << "x的值为：" << str << endl;
//  str = y;
//  cout << "y的值为：" << str << endl;
//  return 0;
//}
