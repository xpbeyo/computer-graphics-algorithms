#include "reflect.h"

void reflect(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & reflected)
{
  reflected.clear();
  reflected.resize(width*height*num_channels);
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      int starting_point = (i + 1) * width * num_channels - j * num_channels - num_channels;
      for (int pos = 0; pos < num_channels; pos++) {
       reflected[i * width * num_channels + j * num_channels + pos] = input[starting_point + pos];
      }
    }
  }
}
