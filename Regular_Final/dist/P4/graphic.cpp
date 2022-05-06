#include  <iostream>
#include "graphic.hpp"

// constructor 
// default set (_x, _y, _z) = (0, 0, 0)
Vec3::Vec3(){
  // your code here 
  _x = 0;
  _y = 0;
  _z = 0;
  
};
// constructor
Vec3::Vec3(const double & _x1, const double & _y1, const double & _z1){
  // your code here
  _x = _x1;
  _y = _y1;
  _z = _z1;

};
// copy constructor 
Vec3::Vec3(const Vec3 & _p){
  // your code here
  _x = _p._x;
  _y = _p._y;
  _z = _p._z;

};

// return value of _x
const double Vec3::x() const{
  // your code here
  return _x;
};

//return value of _y
const double Vec3::y() const{
  // your code here 
  return _y;
};

// return value of _z
const double Vec3::z() const{
  // your code here
  return _z;
}
// modify _x
void Vec3::set_x(const double& _t){
  // your code here
  _x = _t;
};
// modify _y
void Vec3::set_y(const double& _t){
  // your code here
  _y = _t;
};
// modify _z
void Vec3::set_z(const double& _t){
  // your code here
  _z = _t;
};
// operator overloading +
Vec3 Vec3::operator + (const Vec3 &b){
  // your code here
return Vec3(_x + b._x, _y + b._y, _z + b._z );
}

Vec3 Vec3::operator - (const Vec3 &b){
  // your code here
  return Vec3(_x - b._x, _y - b._y, _z - b._z );
}


Vec3 Vec3::operator ^ (const Vec3 &b){
  // your code here
  return Vec3(_y*b._z - _z * b._y, _z*b._x - _x * b._z, _x*b._y - _y * b._x);
};

