#include "rgb_to_hsv.h"
#include <algorithm>
#include <math.h>

void rgb_to_hsv(
  const double r,
  const double g,
  const double b,
  double & h,
  double & s,
  double & v)
{

  double rgb[] = {r, g, b};

  double cmax = *std::max_element(rgb, rgb + 3);
  double cmin = *std::min_element(rgb, rgb + 3);
  
  double delta = cmax - cmin;
  if (delta == 0) {
    h = 0;
  }
  else if (cmax == r) {
    h = 60 * fmod((g - b) / delta, 6);
  }
  else if (cmax == g) {
    h = 60 * ((b - r) / delta + 2);
  }
  else {
    h = 60 * ((r - g) / delta + 4);
  }

  if (cmax == 0) {
    s = 0;
  }
  
  else {
    s = delta / cmax;
  }
  v = cmax;
}
