#ifndef MATERIAL_H
#define MATERIAL_H

#include "global.h"

#include "hittable-list.h"

struct HitRecord;

class Material {
public:
  virtual ~Material() = default;
  virtual bool Scatter(const Ray &input_ray, const HitRecord &hit_rec,
                       Color &attenuation, Ray &scattered_ray) const = 0;
};

class Lambertian : public Material { 
  public:
    Lambertian(const Color &color) : albedo(color) {}
    
    bool Scatter(const Ray &input_ray, const HitRecord &hit_rec, Color &attenuation, Ray &scattered_ray) const override {
      Vec3 scatter_direction = hit_rec.normal + RandomNormalizedVec3();
      
      if(scatter_direction.NearZero())
        scatter_direction = hit_rec.normal;
      
      scattered_ray = Ray(hit_rec.point, scatter_direction);
      attenuation = albedo;
      return true;
    }
    
    private:
    Color albedo;
};


class Metal : public Material {
  public: 
  Metal(const Color &color, double f) : albedo(color), fuzz(f < 1 ? f : 1) {}

   bool Scatter(const Ray &input_ray, const HitRecord &hit_rec, Color &attenuation, Ray &scattered_ray) const override {
    Vec3 reflected = Reflect(Normalized(input_ray.Direction()),hit_rec.normal);
    scattered_ray = Ray(hit_rec.point, reflected + fuzz * RandomNormalizedVec3());
    attenuation = albedo;
    return (DotProduct(scattered_ray.Direction(), hit_rec.normal));
   }
  

  private: 
  Color albedo;
  double fuzz;
};

#endif