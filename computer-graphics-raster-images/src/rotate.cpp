#include "rotate.h"

void rotate(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & rotated)
{
  rotated.clear();
  rotated.resize(height*width*num_channels);
  for (int i = 0; i < width; i++) {
    // how much offset to reach the first channel of
    // the pre-rotated pixel
    int offset = width * num_channels - i * num_channels - num_channels;
    for (int j = 0; j < height; j++) {
      // The starting position of the pre-rotated pixel
      // considering what the current row is
      int starting_pos = j * width * num_channels + offset;
      for (int k = 0; k < num_channels; k++) {
        rotated[i * height * num_channels + j * num_channels + k] = input[starting_pos + k];
      }
    }
  }
}
