#ifndef CAMERA_H
#define CAMERA_H

#include "color.h"
#include "global.h"
#include "render_object.h"
class Camera {
public:
  double aspect_ratio = 1.0;  // width/height
  int img_width = 100;        // width in pixels
  int pixel_sample_size = 10; // amount of random sample per pixel
  int max_depth = 10;         // recursion depth of ray bounces

  void Render(const RenderObject &world);
  Color RayColor(const Ray &ray, int depth, const RenderObject &world) const;

private:
  int img_height;
  double focal_length = 1.0f;
  double viewpoint_height = 2.0f;
  double viewpoint_width;
  Vec3 center;
  Vec3 pixel_00_loc;
  // pixel spacing
  Vec3 pixel_delta_x;
  Vec3 pixel_delta_y;

  void Initialize();
  Vec3 PixelSampleSquare();
  Ray GetRay(int coordinate_x, int coordinate_y);
};

#endif