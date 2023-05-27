/*
 * quote_sudy01.cpp
 *
 *  Created on: 2019Äê8ÔÂ14ÈÕ
 *      Author: Administrator
 */
#include <iostream>
using namespace std;
void useQuote() {
  int i;
  double d;
  int& r = i;
  double&s = d;
  i = 10;
  d = 2.4;
  cout << "i:" << i << endl;
  cout << "r:" << r << endl;
  cout << "d:" << d << endl;
  cout << "s:" << s << endl;
}

void swap(int& x, int& y) {
  int temp;
  temp = x;
  x = y;
  y = temp;
}
void testSwap() {
  int i1 = 100;
  int i2 = 200;
  int& ir1 = i1;
  int& ir2 = i2;
  swap(ir1, ir2);
  cout << ir1 << endl;
  cout << ir2 << endl;
}

double array[] = { 10.1, 20.2, 30.3, 40.4, 50.5 };
double& setValue(int i) {
  return array[i];
}
void testSetValue() {
  setValue(2) = 60.6;
  setValue(3) = 70.7;
  for (int i = 0; i < 5; i++) {
    cout << i << ":" << array[i] << endl;
  }
}
