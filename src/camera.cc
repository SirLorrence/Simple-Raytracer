#include "../include/camera.h"

void Camera::Render(const RenderObject &world) {
  Initialize();

  // Create PPM image

  std::cout << "P3\n" << img_width << 'x' << img_height << "\n255\n";

  for (int y = 0; y < img_height; ++y) {
    // logging the  progress
    std::clog << "\r Lines Remaining:" << (img_height - y) << ' ' << std::flush;
    for (int x = 0; x < img_width; ++x) {
      Vec3 pixel_color = Vec3::Zero(); // white
      // get the aggregated average
      for (int sample = 0; sample < pixel_sample_size; ++sample) {
        Ray ray = GetRay(x, y);
        pixel_color += RayColor(ray, max_depth, world);
      }
      WriteColor(std::cout, pixel_color, pixel_sample_size);
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

Color Camera::RayColor(const Ray &ray, int depth,
                       const RenderObject &world) const {
  HitRecord hit_record;

  // no more light is gathered.
  if (depth <= 0)
    return Color(0, 0, 0);

  if (world.Hit(ray, Interval(0.001, kInfinity), hit_record)) {
    // Diffused
    //    Vec3 direction = RandomOnHemisphere(hit_record.normal);
    // Limbertian
    Vec3 direction = hit_record.normal + RandomNormalizedVec3();
    return 0.5 * RayColor(Ray(hit_record.point, direction), depth - 1, world);
  }

  Vec3 unit_direction = Normalized(ray.Direction());
  double blended_value = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - blended_value) * Color(1.0, 1.0, 1.0) +
         blended_value * Color(0.5, 0.7, 1.0);
}

Ray Camera::GetRay(int coordinate_x, int coordinate_y) {
  Vec3 pixel_center = pixel_00_loc + (coordinate_x * pixel_delta_x) +
                      (coordinate_y * pixel_delta_y);
  Vec3 pixel_sample = pixel_center + PixelSampleSquare();
  // writtin for clarity
  Vec3 origin = center;
  Vec3 direction = pixel_sample - origin;

  return Ray(origin, direction);
}

// Return an random point in the surrounding square of the pixel origin.
Vec3 Camera::PixelSampleSquare() {
  double random_point_x = -0.5 + RandomDouble01();
  double random_point_y = -0.5 + RandomDouble01();
  return (random_point_x * pixel_delta_x) + (random_point_y * pixel_delta_y);
}