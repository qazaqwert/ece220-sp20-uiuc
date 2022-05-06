#include <iostream>
#include "graphic.hpp"
using namespace std;

string bool2str(bool flag){
  string res;
  return (flag)? "\u001b[32mTrue\u001b[0m": "\u001b[31mFalse\u001b[0m";
}

int main(){
  // test default constructor
  Vec3 p1; 
  // test constructor with given arguments
  Vec3 p3(-10, 1, -1);
  std::cout << "Vec3 p1: " << p1 << std::endl;
  std::cout << "Vec3 p3: " << p3 << std::endl;

  // test on set functions
  p1.set_x(3.3);
  p1.set_y(2.3);
  p1.set_z(1.3);
  // test on access function
  std::cout << "Update p1 to (3.3, 2.3, 1.3)\nVec3 p1: " << p1.x()<<", "<<p1.y() <<", "<<p1.z() << std::endl;
  Vec3 p2(1.0, 2.0, 1.5);
  // test on copy constructor
  p2 = p1;
  std::cout << "Vec3 p2 = p1, p2: "<< p2 << std::endl;
  // test on operation overloading +
  std::cout << "p1 + p3 = "<< p1+p3 << std::endl;
  // test on operation overloading -
  std::cout << "p1 - p3 = "<< p1-p3 << std::endl;
  // test on operator overloading ^ 
  std::cout << "Vec3 p1^p3 = "<< (p1^p3) <<std::endl;

  return 0;
}
