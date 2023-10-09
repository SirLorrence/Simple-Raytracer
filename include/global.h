#ifndef GLOBAL_H
#define GLOBAL_H

#include <cmath>
#include <limits>
#include <memory>

constexpr double kInfinity = std::numeric_limits<double>::infinity();
constexpr double kPi = 3.1415926535897932385;

inline double DegreesToRadians(double degrees) { return degrees * kPi / 180.0; }

// Common Headers
#include "interval.h"
#include "ray.h"
#include "vec3.h"

#endif