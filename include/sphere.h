#ifndef SPHERE_H
#define SPHERE_H

#include "global.h"
#include "render_object.h"

class Sphere : public RenderObject {
public:
  Sphere(Vec3 Center, double Raduis) : center(Center), radius(Raduis) {}

  bool Hit(const Ray &r, Interval ray_t, HitRecord &rec) const override;

private:
  Vec3 center;
  double radius;
};

#endif