#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

struct Vec3 {
  double axis[3];

  // initialtion constructors
  Vec3() : axis{0, 0, 0} {}; // default
  Vec3(double init_x, double init_y, double init_z)
      : axis{init_x, init_y, init_z} {};

  double x() const { return axis[0]; }
  double y() const { return axis[1]; }
  double z() const { return axis[2]; }

  // ======== vector operation functions
  // returns the inverse value of the vector
  Vec3 operator-() const { return Vec3(-axis[0], -axis[1], -axis[2]); };
  // returns the axis value based of an array element
  double operator[](int value) const { return axis[value]; }
  // returns the axis address value based on the element selected
  double& operator[](int value) { return axis[value]; }

  //
  Vec3& operator+=(const Vec3& input_vec3) {
    axis[0] += input_vec3[0];
    axis[1] += input_vec3[1];
    axis[2] += input_vec3[2];
    return *this; // dereference to the current vec3
  }

  Vec3& operator*=(double value) {
    axis[0] *= value;
    axis[1] *= value;
    axis[2] *= value;
    return *this;
  }

  Vec3& operator/=(double value) { return *this *= 1 / value; }

  double LengthSquard() const {return axis[0]*axis[0] + axis[1] * axis[1] + axis[2] * axis[2];}
  
  double Length() const { return std::sqrt(LengthSquard()); }
  
};


// Vector Utilies

inline std::ostream& operator<<(std::ostream& out, const Vec3& v){return out<< v.axis[0] << ' ' << v.axis[1] << ' ' << v.axis[2];}

// Math Operators
inline Vec3 operator+(const Vec3& a, const Vec3& b){return Vec3(a.axis[0] + b.axis[0], a.axis[1] + b.axis[1], a.axis[2] + b.axis[2]);}
inline Vec3 operator-(const Vec3& a, const Vec3& b){return Vec3(a.axis[0] - b.axis[0], a.axis[1] - b.axis[1], a.axis[2] - b.axis[2]);}

inline Vec3 operator*(const Vec3& a, const Vec3& b){return Vec3(a.axis[0] * b.axis[0], a.axis[1] * b.axis[1], a.axis[2] * b.axis[2]);}
inline Vec3 operator*(double value, const Vec3& v){return Vec3(value * v.axis[0], value * v.axis[1], value * v.axis[2]);}
inline Vec3 operator*(const Vec3& v, double value){return value * v;}
// using const for now
inline Vec3 operator/(const Vec3& v, double value){return (1/value) * v;}

inline double DotProduct(const Vec3& a, const Vec3& b){
  return
      a.axis[0] * b.axis[0] +
      a.axis[1] * b.axis[1] +
      a.axis[2] * b.axis[2];
}

inline Vec3 cross_product(const Vec3& a, const Vec3& b){
  return Vec3(
      a.y() * b.z() - a.z() * a.y(),
      a.z() * b.x() - a.x() * b.z(),
      a.x() * b.y() - a.y() * b.x()
      );
}

inline Vec3 Normalized(Vec3 v){return v/v.Length();}

#endif