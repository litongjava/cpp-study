/*
 * platfrom_study_01.cpp
 *
 *  Created on: 2019Äê8ÔÂ24ÈÕ
 *      Author: litong
 */
#include "platfrom.h"
#include <iostream>
using namespace std;

void coutPlatform() {
#ifdef _WIN32
  cout << "win32" << endl;
#endif

#ifdef _WIN64
  cout <<"win64"<<endl;
#else
  cout << "linux" << endl;
#endif

}

