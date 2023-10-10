#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "interval.h"
#include "object.h"

#include <vector>

struct HittableList : public Object {
  std::vector<std::shared_ptr<Object>> objects;

  HittableList() {}
  HittableList(std::shared_ptr<Object> object) { Add(object); }

  void Clear() { objects.clear(); }

  void Add(std::shared_ptr<Object> obj) { objects.push_back(obj); }

  bool Hit(const Ray &ray, Interval ray_t,
           HitRecord &hit_record) const override {
    HitRecord temp_record;
    bool hit_anything = false;
    double closest = ray_t.max;

    // TODO: make this an Object Type
    for (const auto &obj : objects) {
      if (obj->Hit(ray, Interval(ray_t.min, closest), temp_record)) {
        hit_anything = true;
        closest = temp_record.scaler;
        hit_record = temp_record;
      }
    }
    return hit_anything;
  }
};

#endif