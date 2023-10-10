#include "../include/camera.h"

void Camera::Render(const Object &world) {
  Initialize();

  // Create PPM image

  std::cout << "P3\n" << img_width << 'x' << img_height << "\n255\n";

  for (int y = 0; y < img_height; ++y) {
    // logging the  progress
    std::clog << "\r Lines Remaining:" << (img_height - y) << ' ' << std::flush;
    for (int x = 0; x < img_width; ++x) {
      Vec3 pixel_center =
          pixel_00_loc + (x * pixel_delta_x) + (y * pixel_delta_y);
      Vec3 ray_direction = pixel_center - center;
      Ray ray(center, ray_direction);
      Vec3 pixel_color = RayColor(ray, world);
      WriteColor(std::cout, pixel_color);
    }
  }
  std::clog << "\r Done.                    \n"; // extra white space to
                                                 // overwrite any logs
}

void Camera::Initialize() {
  img_height = static_cast<int>(img_width / aspect_ratio);
  img_height = (img_height < 1) ? 1 : img_height;

  viewpoint_width =
      viewpoint_height * (static_cast<double>(img_width) / img_height);
  center = Vec3::Zero();

  Vec3 viewport_x = Vec3(viewpoint_width, 0, 0);
  Vec3 viewport_y = Vec3(0, -viewpoint_height, 0);

  pixel_delta_x = viewport_x / img_width;
  pixel_delta_y = viewport_y / img_height;

  Vec3 viewport_upper_left =
      center - Vec3(0, 0, focal_length) - viewport_x / 2 - viewport_y / 2;
  pixel_00_loc = viewport_upper_left + 0.5 * (pixel_delta_x + pixel_delta_y);
}

Color Camera::RayColor(const Ray &ray, const Object &world) const {
  HitRecord hit_record;
  if (world.Hit(ray, Interval(0, kInfinity), hit_record)) {
    return 0.5 * (hit_record.normal + Color(1, 1, 1));
  }

  Vec3 unit_direction = Normalized(ray.Direction());
  double blended_value = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - blended_value) * Color(1.0, 1.0, 1.0) +
         blended_value * Color(0.5, 0.7, 1.0);
}