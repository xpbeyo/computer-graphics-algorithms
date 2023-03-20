#include "box_box_intersect.h"
bool box_box_intersect(
  const BoundingBox & A,
  const BoundingBox & B)
{
  for (int i = 0; i < A.max_corner.cols(); i++) {
    if (!(A.min_corner(0, i) <= B.max_corner(0, i) && A.max_corner(0, i) >= B.min_corner(0, i) ||
         (B.min_corner(0, i) <= A.max_corner(0, i) && B.max_corner(0, i) >= A.min_corner(0, i)))) {
      return false;
    }
  }
  return true;
}

