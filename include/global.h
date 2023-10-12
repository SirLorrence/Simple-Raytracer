#ifndef GLOBAL_H
#define GLOBAL_H

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

constexpr double kInfinity = std::numeric_limits<double>::infinity();
constexpr double kPi = 3.1415926535897932385;

inline double DegreesToRadians(double degrees) { return degrees * kPi / 180.0; }

// returns a value between 0 - 1
inline double RandomDouble01() { return rand() / (RAND_MAX + 1.0); }

inline double RandomDouble(double min, double max) {
  return min + (max - min) * RandomDouble01();
}

// Common Headers
#include "interval.h"
#include "ray.h"
#include "vec3.h"

#endif