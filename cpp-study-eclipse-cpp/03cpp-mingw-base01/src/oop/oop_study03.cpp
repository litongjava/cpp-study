#include <iostream>
#include <oop.h>

using namespace std;
class Box {
  double width;
public:
  friend void printWidth(Box box);
  void setWidth(double wid);
};
void Box::setWidth(double wid) {
  width = wid;
}

void printWidth(Box box) {
  cout << box.width << endl;
}
void testFriend() {
  Box box1;
  box1.setWidth(100);
  printWidth(box1);
}
