#include <iostream>
#include <string>
using namespace std;
int main_string(int argc,char* argv[]){
  string filepath=argv[0];
  cout << filepath.c_str()<<endl;
  return 0;
}
