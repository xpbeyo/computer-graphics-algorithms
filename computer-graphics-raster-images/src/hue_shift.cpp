#include "hue_shift.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"

void hue_shift(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double shift,
  std::vector<unsigned char> & shifted)
{
  shifted.clear();
  shifted.resize(rgb.size());
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      double h, s, v;
      double r, g, b;
      r = rgb[i * width * 3 + j * 3];
      g = rgb[i * width * 3 + j * 3 + 1];
      b = rgb[i * width * 3 + j * 3 + 2];
      rgb_to_hsv(r, g, b, h, s, v);
      h += shift;
      h = fmod(h, 360);
      if (h < 0) {
        h += 360;
      }
      hsv_to_rgb(h, s, v, r, g, b);
      shifted[i * width * 3 + j * 3] = r;
      shifted[i * width * 3 + j * 3 + 1] = g;
      shifted[i * width * 3 + j * 3 + 2] = b;
    }
  }
}
