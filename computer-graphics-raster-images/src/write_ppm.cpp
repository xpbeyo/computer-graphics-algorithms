#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  assert(
    (num_channels == 3 || num_channels == 1) &&
    ".ppm only supports RGB or grayscale images");
  std::ofstream ppm_file;
  ppm_file.open(filename);
  if (!ppm_file.is_open()) {
    std::cout << "failed to open file." << std::endl;
    return false;
  }
  if (num_channels == 3) {
    ppm_file << "P3" << std::endl;
  }
  else {
    ppm_file << "P2" << std::endl;
  }

  ppm_file << (std::to_string(width) + " " + std::to_string(height)) << std::endl;
  ppm_file << "255" << std::endl;
  for (int i = 0; i < height; i++) {
    std::string line = "";
    for (int j = 0; j < width * num_channels; j++) {
      line = line.append(std::to_string(data[width * num_channels * i + j]));
      line = line.append(" ");
    }
    ppm_file << line << std::endl;
  }
  ppm_file.close();
  return true;
}
