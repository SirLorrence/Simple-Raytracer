#include "../include/global.h"

#include "../include/camera.h"
#include "../include/color.h"
#include "../include/hittable-list.h"
#include "../include/material.h"
#include "../include/sphere.h"

int main() {
  // World Objects
  HittableList world;
  auto material_ground = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
  auto material_center = std::make_shared<Lambertian>(Color(0.1,0.2,0.5));
  auto material_left = std::make_shared<Dielectric>(1.5);
  auto material_right = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 0.0);

  world.Add(std::make_shared<Sphere> (Vec3(0, -100.5, -1), 100.0, material_ground));
  world.Add(std::make_shared<Sphere> (Vec3(0, 0, -1), 0.5, material_center));
  world.Add(std::make_shared<Sphere> (Vec3(-1.0, 0, -1), 0.5, material_left));
  world.Add(std::make_shared<Sphere> (Vec3(-1.0, 0, -1), -0.4, material_left));
  world.Add(std::make_shared<Sphere> (Vec3(1.0,0, -1), 0.5, material_right));

  Camera main_camera;
  main_camera.aspect_ratio = 16.0 / 9.0;
  main_camera.img_width = 640;
  main_camera.pixel_sample_size = 100;
  main_camera.max_depth = 50;

  main_camera.v_fov = 20;
  main_camera.look_from = Vec3(-2,2,1);
  
  main_camera.defocus_angle = 10.0;
  main_camera.focus_distance = 3.4;

  main_camera.Render(world);
}
