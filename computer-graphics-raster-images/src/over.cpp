#include "over.h"
#include <cassert>
#include <math.h>

void over(
  const std::vector<unsigned char> & A,
  const std::vector<unsigned char> & B,
  const int & width,
  const int & height,
  std::vector<unsigned char> & C)
{
  C.resize(A.size());
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      double alpha_a = A[i * width * 4 + j * 4 + 3] / 255.0;
      double alpha_b = B[i * width * 4 + j * 4 + 3] / 255.0;
      assert(0 <= alpha_a && alpha_a <= 1);
      assert(0 <= alpha_b && alpha_b <= 1);
      for (int k = 0; k < 3; k++) {
        double color_a = A[i * width * 4 + j * 4 + k];
        double color_b = B[i * width * 4 + j * 4 + k];
        C[i * width * 4 + j * 4 + k] = color_a * alpha_a + color_b * alpha_b * (1 - alpha_a);
      }
      C[i * width * 4 + j * 4 + 3] = 255;
    }
  }
}
