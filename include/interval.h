#ifndef INTERVAL_H
#define INTERVAL_H

#include "global.h"
struct Interval {
  double min;
  double max;
  // Default
  Interval() : min(+kInfinity), max(-kInfinity) {}
  Interval(double Min, double Max) : min(Min), max(Max) {}

  bool Contains(double value) { return min <= value && max >= value; }
  bool Surrounds(double value) { return min < value && max > value; }

  static const Interval kEmpty;
  static const Interval kUniverse;
};

const static Interval kEmpty(+kInfinity, -kInfinity);
const static Interval kUniverse(-kInfinity, +kInfinity);

#endif