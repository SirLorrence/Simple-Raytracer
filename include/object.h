#ifndef OBJECT_H
#define OBJECT_H

#include "global.h"

struct HitRecord {
  Vec3 point;
  Vec3 normal;
  double scaler; // distance or scaler
  bool front_face;

  // Sets the hit record normal vector.

  void SetFaceNormal(const Ray &ray, const Vec3 &outward_normal) {
    front_face = DotProduct(ray.Direction(), outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
  }
};

class Object {
public:
  virtual ~Object() = default;
  virtual bool Hit(const Ray &r, Interval ray_t, HitRecord &rec) const = 0;
};

#endif