#include <iostream>
#include <struct.h>
using namespace std;
static struct {
  char *api_base;
  char *app_key;
  char *voice;
  char *audio_type;
  int buffer_size;
  int buffer_max_size;
  int auto_reload;
} globals;

void testToString() {
  globals.auto_reload = 1;
  cout << "hello,world" << endl;
  //cout << globals<<endl; //±àÒë³ö´í
  cout << globals.auto_reload << endl;
}
