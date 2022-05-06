#pragma once
#include <iostream>
#include <string>

class Vec3{
  private:
    double _x;
    double _y;
    double _z;
  public: 
    Vec3();
    Vec3(const double & _x1, const double & _y1, const double &_z1);
    Vec3(const Vec3 & _p);
    ~Vec3() {}; // you don't need to implement destrcutor
    const double x() const;
    const double y() const;
    const double z() const;
    void set_x(const double& _t);
    void set_y(const double& _t);
    void set_z(const double& _t);
    Vec3 operator + (const Vec3 &b);
    Vec3 operator - (const Vec3 &b);
    Vec3 operator ^ (const Vec3 &b);

    // you don't need to implement operator <<
    friend std::ostream & operator << (std::ostream &out, const Vec3 &v){
      out<<"("<<v._x<<", "<<v._y<<", "<<v._z<<")";
      return out;
    };
};

