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
  
  center = look_from;

  // viewport dimensions
  // double focal_length = (look_from - look_at).Length();
  double theta = DegreesToRadians(v_fov);
  double h = std::tan(theta/2);
  double viewpoint_height = 2 * h * focus_distance;
  double viewpoint_width =
      viewpoint_height * (static_cast<double>(img_width) / img_height);

  // calculate basis vectors for camera frame
  w = Normalized(look_from - look_at);
  u = Normalized(CrossProduct(view_up,w));
  v = CrossProduct(w,u);


  Vec3 viewport_x = viewpoint_width * u;
  Vec3 viewport_y = viewpoint_height * -v;

  pixel_delta_x = viewport_x / img_width;
  pixel_delta_y = viewport_y / img_height;

  Vec3 viewport_upper_left =
      center - (focus_distance * w)- viewport_x / 2 - viewport_y / 2;
  pixel_00_loc = viewport_upper_left + 0.5 * (pixel_delta_x + pixel_delta_y);

  // defocus disk
  double defocus_radius = focus_distance * std::tan(DegreesToRadians(defocus_angle/2));
  defocus_disk_x = u * defocus_radius;
  defocus_disk_y = v * defocus_radius;
}

Color Camera::RayColor(const Ray &ray, int depth,
                       const RenderObject &world) const {
  HitRecord hit_record;

  // no more light is gathered.
  if (depth <= 0)
    return Color(0, 0, 0);

  if (world.Hit(ray, Interval(0.001, kInfinity), hit_record)) {
    Ray scatted_ray;
    Color attenuation;
    if(hit_record.material->Scatter(ray,hit_record,attenuation,scatted_ray))
      return attenuation * RayColor(scatted_ray, depth -1 , world);
    return Color(0,0,0);

    // Diffused
    //    Vec3 direction = RandomOnHemisphere(hit_record.normal);
    // Limbertian
  //  Vec3 direction = hit_record.normal + RandomNormalizedVec3();s
//    return 0.5 * RayColor(Ray(hit_record.point, direction), depth - 1, world);
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
  

  Vec3 origin = (defocus_angle <= 0)? center : DefocusDiskSample();
  Vec3 direction = pixel_sample - origin;
  return Ray(origin, direction);
}

Vec3 Camera::DefocusDiskSample() const {
  Vec3 v = RandomInDisk();
  return center + (v[0] * defocus_disk_x) + (v[1] * defocus_disk_y);
}


// Return an random point in the surrounding square of the pixel origin.
Vec3 Camera::PixelSampleSquare() {
  double random_point_x = -0.5 + RandomDouble01();
  double random_point_y = -0.5 + RandomDouble01();
  return (random_point_x * pixel_delta_x) + (random_point_y * pixel_delta_y);
}