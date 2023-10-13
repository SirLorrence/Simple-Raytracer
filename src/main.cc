#include "../include/camera.h"
#include "../include/global.h"
#include "../include/hittable-list.h"
#include "../include/sphere.h"

int main() {
  // World Objects
  HittableList world;
  world.Add(std::make_shared<Sphere>(Vec3(0, 0, -1), 0.5));
  world.Add(std::make_shared<Sphere>(Vec3(0, -100.5, -1), 100));

  Camera main_camera;
  main_camera.aspect_ratio = 16.0 / 9.0;
  main_camera.img_width = 640;
  main_camera.pixel_sample_size = 100;
  main_camera.max_depth = 50;

  main_camera.Render(world);
}
