#include "../include/color.h"
#include "../include/ray.h"
#include "../include/vec3.h"

#include <iostream>

bool HitSphere(const Vec3& center, const Ray& ray, float radius) {
  Vec3 origin_center = ray.Origin() - center;
  double a = DotProduct(ray.Direction(), ray.Direction());
  double b = 2.0 * DotProduct(origin_center, ray.Direction());
  double c = DotProduct(origin_center, origin_center) - radius * radius;
  float  discriminant = b * b - 4.0f * a * c;
  return (discriminant >= 0.0f);
}

Color RayColor(const Ray& r) {
  if (HitSphere(Vec3(0, 0, -1), r, 0.5f))
    return Color(1, 0, 0);

  Vec3 unit_direction = Normalized(r.Direction());
  double blended_value = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - blended_value) * Color(1.0, 1.0, 1.0) + blended_value * Color(0.5, 0.7, 1.0);
}


int main() {
  // image size in pixels (using c20)
  float aspect_ratio = 16.0f / 9.0f; // (width/height)
  constexpr int img_width = 400;

  // calculate the image height based on width
  int img_height = static_cast<int>(img_width / aspect_ratio);
  img_height = (img_height < 1) ? 1 : img_height;

  // Camera Setup
  float focal_length = 1.0f;
  float viewpoint_height = 2.0f;
  double viewpoint_width = viewpoint_height * (static_cast<double>(img_width) / img_height);
  Vec3 cam_center = Vec3(); // vector zero

  // calculate the vec across the h and v viewport edge
  Vec3 viewport_x = Vec3(viewpoint_width, 0, 0);
  Vec3 viewport_y = Vec3(0, viewpoint_height, 0); // inverse for right hand coords

  // calculate the h and v delta vec from pixel to pixel
  Vec3 pixel_delta_x = viewport_x / img_width;
  Vec3 pixel_delta_y = viewport_y / img_height;

  // calculate the location of the upper left pixel
  Vec3 viewport_upper_left =
      cam_center - Vec3(0, 0, focal_length) - viewport_x / 2 - viewport_y / 2;
  Vec3 pixell00_loc =
      viewport_upper_left + 0.5 * (pixel_delta_x + pixel_delta_y);

  std::cout << "P3\n" << img_width << 'x' << img_height << "\n255\n";

  for (int y = 0; y < img_height; ++y) {
    // logging the  progress
    std::clog << "\r Lines Remaining:" << (img_height - y) << ' ' << std::flush;
    for (int x = 0; x < img_width; ++x) {
      Vec3 pixel_center = pixell00_loc + (x * pixel_delta_x) + (y * pixel_delta_y);
      Vec3 ray_direction = pixel_center - cam_center;
      Ray ray(cam_center, ray_direction);
      Vec3 pixel_color = RayColor(ray);
      write_color(std::cout, pixel_color);
    }
  }
  std::clog << "\r Done.                    \n"; // extra white space to overwrite any logs
}

// image size in pixels (using c20)
//  constexpr int height = 256;
//  constexpr int width = height; // 1x1 size
//
////  std::cout<<"P3\n" << height << 'x' << width << "\n255\n";
////
////  for(int y = 0; y < height; ++y){
////    //logging the  progress
////    std::clog <<"\r Lines Remaining:" << (height - y) << ' ' <<
/// std::flush; /    for(int x = 0; x < width; ++x){ /      double r =
/// double(x)/width - 1; /      double g = double(y)/height - 1; /      Vec3
/// pixel_color = Color(r,g,0); /      write_color(std::cout, pixel_color);
//
//
////      // want to be specific on how i cast things
////      double r = static_cast<double>(x)/(width - 1);
////      double g = static_cast<double>(y)/(height - 1);
////      double b = 0.0;
////
////      double scaler = 255.999; // multiplier/max colour
////
////      int whole_r = static_cast<int>(scaler * r);
////      int whole_g = static_cast<int>(scaler * g);
////      int whole_b = static_cast<int>(scaler * b); //will always be 0
////
////      std::cout<< whole_r << ' ' << whole_g << ' ' << whole_b << '\n';
////    }
////  }
////  std::clog << "\r Done. \n";
