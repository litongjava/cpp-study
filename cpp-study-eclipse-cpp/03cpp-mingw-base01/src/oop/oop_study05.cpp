#include <iostream>
#include <oop.h>
using namespace std;
class BigBox {
private:
  double length;
  double breadth;
  double height;
public:
  BigBox(double l, double b, double h) {
    length = l;
    breadth = b;
    height = h;
  }
  double getVolume() {
    return length * breadth * height;
  }
  int compare(BigBox box) {
    return this->getVolume() > box.getVolume();
  }
};

void testThisPoint() {
  BigBox box1(3.3, 1.2, 1.5);
  BigBox box2(8.5, 6.0, 2.0);
  cout << box1.compare(box2) << endl;
}
