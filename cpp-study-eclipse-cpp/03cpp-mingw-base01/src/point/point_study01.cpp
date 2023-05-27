#include <iostream>
#include <ctime>
#include <cstdlib>
#include <point.h>
using namespace std;
void getAddress() {
  int var1;
  char var2[10];
  cout << &var1 << endl;
  cout << &var2 << endl;
}
void getValue() {
  int var1 = 10;
  int *p = &var1;
  cout << *p << endl;
  cout << p << endl;
}
void pointArithmetic() {
  int MAX = 3;
  int array[] = { 10, 20, 30 };
  int *ptr;
  ptr = array; //指向数组,不需要使用&符号
  for (int i = 0; i < MAX; i++) {
    cout << "address:" << ptr << endl;
    cout << "value:" << *ptr << endl;
    ptr++;
  }
}

void pointCompare() {
  int max = 3;
  int array[] = { 10, 20, 30 };
  int *ptr;
  ptr = array; //指向数组的第一个元素
  while (ptr <= &array[max - 1]) {
    cout << "address:" << ptr << endl;
    cout << "value:" << *ptr << endl;
    ptr++;
  }
}
void pointAndArray() {
  int array[] = { 10, 20, 30 };
  *(array + 2) = 40; //为数组的第二个元素赋值
  for (int i = 0; i < 3; i++) {
    cout << array[i] << endl;
  }
}

void pointPointPoint() {
  int var = 10;
  int *ptr = &var;
  int **ptrr = &ptr;
  cout << "var value:" << var << endl;
  cout << "ptr value:" << *ptr << endl;
  cout << "ptrr value:" << **ptrr << endl;
}

void pointFunction(unsigned long *ptr) {
  *ptr = time(NULL); //获取当前的秒数
}

void getSecond() {
  unsigned long var;
  pointFunction(&var);
  cout << var << endl;
}

double getAverage(int *arr, int size) {
  int i, sum = 0;
  double avg;
  for (i = 0; i < size; i++) {
    sum += arr[i];
  }
  avg = sum / size;
  return avg;
}

void testAverage() {
  int balance[5] = { 10, 20, 30, 40, 50 };
  double avg = getAverage(balance, 5);
  cout << avg << endl;
}

int *getRandom() {
  static int r[10];
  srand((unsigned) time(NULL));
  for (int i = 0; i < 10; i++) {
    r[i] = rand();
    cout << r[i] << endl;
  }
  return r;
}

void testRandom() {
  int *p;
  p = getRandom();
  for (int i = 0; i < 10; i++) {
    cout << i << ":" << *(p + i) << endl;
  }
}
