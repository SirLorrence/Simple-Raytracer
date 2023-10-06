#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray {
  public:
  // contructors
    Ray(){}
    Ray(const Vec3& origin, const Vec3& direction) : p_origin(origin), p_direction(direction) {}
  
    Vec3 Origin() const {return p_origin;}
    Vec3 Direction() const {return p_direction;}
  
    Vec3 Scaler(double value){return p_origin + value * p_direction;}
  
  
  private:
    // p for point (to reduce name verbosity)
    Vec3 p_origin;
    Vec3 p_direction;
};

#endif