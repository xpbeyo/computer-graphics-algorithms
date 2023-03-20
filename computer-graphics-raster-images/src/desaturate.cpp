#include "desaturate.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"

void desaturate(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double factor,
  std::vector<unsigned char> & desaturated)
{
  desaturated.resize(rgb.size());
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      double r, g, b;
      double h, s, v;
      r = rgb[i * width * 3 + j * 3];
      g = rgb[i * width * 3 + j * 3 + 1];
      b = rgb[i * width * 3 + j * 3 + 2];
      rgb_to_hsv(r, g, b, h, s, v);
      s = s * (1 - factor);
      hsv_to_rgb(h, s, v, r, g, b);
      desaturated[i * width * 3 + j * 3] = r;
      desaturated[i * width * 3 + j * 3 + 1] = g;
      desaturated[i * width * 3 + j * 3 + 2] = b;
    }
  }
}
