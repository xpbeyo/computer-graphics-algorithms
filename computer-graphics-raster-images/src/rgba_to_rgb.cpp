#include "rgba_to_rgb.h"

void rgba_to_rgb(
  const std::vector<unsigned char> & rgba,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.clear();
  rgb.resize(height*width*3);
  int counter = 0;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      unsigned char alpha = rgba[i * width * 4 + j * 4 + 3] / 255;
      for (int k = 0; k < 3; k++) {
        rgb[i * width * 3 + j * 3 + k] = rgba[i * width * 4 + j * 4 + k] * alpha; 
      }
    }
  }
}
