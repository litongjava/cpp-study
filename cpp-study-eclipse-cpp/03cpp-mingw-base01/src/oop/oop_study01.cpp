#include <iostream>
#include <oop.h>

using namespace std;
class Box {
public:
  double length;
  double breadth;
  double height;
  double getVloume() {
    return length * breadth * height;
  }
};
double getVolumn(Box box) {
  double volume;
  volume = box.length * box.breadth * box.height;
  return volume;
}
void testGetVolume() {
  Box box1;
  box1.length = 1.1;
  box1.breadth = 2.2;
  box1.height = 3.3;
  double volume = getVolumn(box1);
  cout << volume << endl;
}

void testGetBoxVolume() {
  Box box1;
  box1.length = 1.2;
  box1.breadth = 2.3;
  box1.height = 3.4;
  double volume = box1.getVloume();
  cout << volume << endl;
}
class Line {
public:
  double length;
  void setLength(double length);
  double getLenght();
  Line(int len); //构造函数
  Line(const Line &obj); //拷贝构造函数
  ~Line(); //析构函数
private:
  int *ptr;

};
Line::Line(int len) { // @suppress("Class members should be properly initialized")
  ptr = new int;
  *ptr = len;
  cout << "line is init" << endl;
}
Line::Line(const Line &obj) { // @suppress("Class members should be properly initialized")
  ptr = new int;
  *ptr = *obj.ptr;
}
Line::~Line() {
  cout << "line is close" << endl;
  delete ptr;
}
double Line::getLenght() {
  return length;
}
void Line::setLength(double len) {
  length = len;
}

void getPublic() {
  Line line(10);
  line.setLength(12.0);
  cout << line.getLenght() << endl;
}
class C {
public:
  double x;
  double y;
  double z;
  C(double a, double b, double c);
};
C::C(double a, double b, double c) :
    x(a), y(b), z(c) {
  cout << "init end" << endl;
  cout << a << b << c << endl;
}
void initField() {
  double a = 11.1;
  double b = 22.2;
  double c = 33.3;
  C cc(a, b, c);
}

void testDispaly(){
  Line line(10);
}
