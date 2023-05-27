//============================================================================
// Name        : 03cpp-cygwin-base01.cpp
// Author      : litong
// Version     :
// Copyright   : no
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int main() {
#ifdef _WIN32
  cout << "win32" << endl;
#endif

#ifdef _WIN64
  cout <<"win64"<<endl;
#else
  cout << "linux" << endl;
#endif
  return 0;
}
