#ifndef CAMERA_H
#define CAMERA_H

#include "global.h"

#include "color.h"
#include "render_object.h"
#include "material.h"

#include <iostream>

class Camera {
public:
  double aspect_ratio = 1.0;  // width/height
  int img_width = 100;        // width in pixels
  int pixel_sample_size = 10; // amount of random sample per pixel
  int max_depth = 10;         // recursion depth of ray bounces

  double v_fov = 90; 
  Vec3 look_from = Vec3(0,0,0); // z = -1 breaks it - creating a blank render
  Vec3 look_at = Vec3(0,0,-1);
  Vec3 view_up = Vec3(0,1,0);

  void Render(const RenderObject &world);
  Color RayColor(const Ray &ray, int depth, const RenderObject &world) const;

private:
  int img_height;
  Vec3 center;
  Vec3 pixel_00_loc;

  // pixel spacing
  Vec3 pixel_delta_x;
  Vec3 pixel_delta_y;

  // Camera frame basis
  Vec3 u;
  Vec3 v;
  Vec3 w;

  void Initialize();
  Vec3 PixelSampleSquare();
  Ray GetRay(int coordinate_x, int coordinate_y);
};

#endif