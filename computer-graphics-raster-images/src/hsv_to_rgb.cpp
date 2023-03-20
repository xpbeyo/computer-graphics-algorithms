#include "hsv_to_rgb.h"
#include <cmath>
#include <math.h>

void hsv_to_rgb(
  const double h,
  const double s,
  const double v,
  double & r,
  double & g,
  double & b)
{
  double c = v * s;
  double h_ = h / 60.0;
  double x = c * (1 - std::abs(fmod(h_, 2) - 1));
  if (0 <= h_ && h_ <= 1) {
    r = c;
    g = x;
    b = 0;
  }

  else if (1 < h_ && h_ <= 2) {
    r = x;
    g = c;
    b = 0;
  }
  else if (2 < h_ && h_ <= 3) {
    r = 0;
    g = c;
    b = x;
  }
  else if (3 < h_ && h_ <= 4) {
    r = 0;
    g = x;
    b = c;
  }
  else if (4 < h_ && h_ <= 5) {
    r = x;
    g = 0;
    b = c;

  }
  else {
    r = c;
    g = 0;
    b = x;
  }

  double m = v - c;
  r += m;
  g += m;
  b += m;
}
