#ifndef COLOR_H
#define COLOR_H

#include "interval.h"

#include <iostream>

using Color = Vec3;
inline double LinearToGamma(double linear_component) {
  return std::sqrt(linear_component);
}
inline void WriteColor(std::ostream &out, Color pixel_color,
                       int pixel_sample_size) {
  double r = pixel_color.x();
  double g = pixel_color.y();
  double b = pixel_color.z();

  // divbing the color by n samples
  double scale = 1.0 / pixel_sample_size;
  r *= scale;
  b *= scale;
  g *= scale;

  // Apply the linear to gamma transform
  r = LinearToGamma(r);
  g = LinearToGamma(g);
  b = LinearToGamma(b);

  static const Interval color_intensity(0.000, 0.999);

  out << static_cast<int>(256 * color_intensity.Clamp(r)) << ' '
      << static_cast<int>(256 * color_intensity.Clamp(g)) << ' '
      << static_cast<int>(256 * color_intensity.Clamp(b)) << '\n';
}

#endif