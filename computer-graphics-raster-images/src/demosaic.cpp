#include "demosaic.h"

unsigned char get_color(
  const std::vector<unsigned char> & bayer,
  const int & width,
  const int & height,
  const int & i, 
  const int & j) 
{
  if (i < 0 || j < 0 || i >= height || j >= width) {
    return 0;
  }

  else {
    return bayer[i * width + j];
  }
}

unsigned char avg_left_right(
  const std::vector<unsigned char> & bayer,
  const int & width,
  const int & height,
  const int & i, 
  const int & j) 
{
  return 
    (
      get_color(bayer, width, height, i, j - 1) +
      get_color(bayer, width, height, i, j + 1)
    ) / 2;
}

unsigned char avg_up_down(
  const std::vector<unsigned char> & bayer,
  const int & width,
  const int & height,
  const int & i, 
  const int & j) 
{
 return 
  (
   get_color(bayer, width, height, i - 1, j) +
   get_color(bayer, width, height, i + 1, j)
  ) / 2; 
}

unsigned char avg_neightbour(
  const std::vector<unsigned char> & bayer,
  const int & width,
  const int & height,
  const int & i, 
  const int & j) 
{
  return 
    (
      get_color(bayer, width, height, i - 1, j) +
      get_color(bayer, width, height, i + 1, j) +
      get_color(bayer, width, height, i, j - 1) +
      get_color(bayer, width, height, i, j + 1)
    ) / 4;
}

unsigned char avg_diag(
  const std::vector<unsigned char> & bayer,
  const int & width,
  const int & height,
  const int & i, 
  const int & j) 
{
  return
    (
      get_color(bayer, width, height, i - 1, j - 1) +
      get_color(bayer, width, height, i - 1, j + 1) +
      get_color(bayer, width, height, i + 1, j - 1) +
      get_color(bayer, width, height, i + 1, j + 1)
    ) / 4;
}

void assign_color(
  std::vector<unsigned char> & rgb,
  const int & width,
  const int & i,
  const int & j,
  const unsigned char & r,
  const unsigned char & g,
  const unsigned char & b)
{
  rgb[i * width * 3 + j * 3] = r;
  rgb[i * width * 3 + j * 3 + 1] = g;
  rgb[i * width * 3 + j * 3 + 2] = b;
}

void green_demosaic(
  const std::vector<unsigned char> & bayer,
  std::vector<unsigned char> & rgb,
  const int & width,
  const int & height,
  const int & i,
  const int & j)
{
  unsigned char r, g, b;
  if (j % 2 == 0) {
    r = avg_up_down(bayer, width, height, i, j);
    g = bayer[i * width + j];
    b = avg_left_right(bayer, width, height, i, j);
  }

  else {
    r = avg_left_right(bayer, width, height, i, j);
    g = bayer[i * width + j];
    b = avg_up_down(bayer, width, height, i, j);
  }

  assign_color(rgb, width, i, j, r, g, b);
}

void red_demosaic(
  const std::vector<unsigned char> & bayer,
  std::vector<unsigned char> & rgb,
  const int & width,
  const int & height,
  const int & i,
  const int & j)
{
  unsigned char r, g, b;
  r = bayer[i * width + j];
  g = avg_neightbour(bayer, width, height, i, j);
  b = avg_diag(bayer, width, height, i, j);

  assign_color(rgb, width, i, j, r, g, b);
}


void blue_demosaic(
  const std::vector<unsigned char> & bayer,
  std::vector<unsigned char> & rgb,
  const int & width,
  const int & height,
  const int & i,
  const int & j)
{
  unsigned char r, g, b;
  r = avg_diag(bayer, width, height, i, j);
  g = avg_neightbour(bayer, width, height, i, j);
  b = bayer[i * width + j];

  assign_color(rgb, width, i, j, r, g, b);
}

void demosaic(
  const std::vector<unsigned char> & bayer,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.clear();
  rgb.resize(width*height*3);
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (i % 2 == j % 2) { // Green
        green_demosaic(bayer, rgb, width, height, i, j);
      }

      else if (i % 2 == 0 && j % 2 != 0) { // Blue
        blue_demosaic(bayer, rgb, width, height, i, j);
      }

      else { // Red
        red_demosaic(bayer, rgb, width, height, i, j);
      }
    }
  }
}
