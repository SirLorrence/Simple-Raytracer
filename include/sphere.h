#ifndef SPHERE_H
#define SPHERE_H

#include "global.h"
#include "object.h"

class Sphere : public Object {
public:
  Sphere(Vec3 Center, double Raduis) : center(Center), radius(Raduis) {}

  bool Hit(const Ray &r, Interval ray_t, HitRecord &rec) const override;

private:
  Vec3 center;
  double radius;
};

#endif