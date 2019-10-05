/*
 * if_study_01.cpp
 *
 *  Created on: 2019年8月23日
 *      Author: Administrator
 */
#include <iostream>
#include "if.h"
using namespace std;

static struct {
  int auto_reload;
} global;
void testif1() {
  if (global.auto_reload) {
    cout << "执行" << endl;
  } else {
    cout << "没有执行" << endl;
  }
}
