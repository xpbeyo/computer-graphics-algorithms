#include "rgb_to_gray.h"
#include <cassert>
unsigned char rgb_to_gray_pixel(std::vector<unsigned char> rgb_pixel) {
  assert(rgb_pixel.size() == 3);
  return rgb_pixel[0] * 0.2126 + rgb_pixel[1] * 0.7152 + rgb_pixel[2] * 0.0722;
}

void rgb_to_gray(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  std::vector<unsigned char> & gray)
{
  gray.clear();
  gray.resize(height*width);
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      gray[i * width + j] = rgb_to_gray_pixel(
        std::vector<unsigned char>(
          rgb.begin() + i * width * 3 + j * 3,
          rgb.begin() + i * width * 3 + j * 3 + 3
        )
      );
    }
  }
}

