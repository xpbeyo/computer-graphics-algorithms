#include "insert_box_into_box.h"
void insert_box_into_box(
  const BoundingBox & A,
  BoundingBox & B)
{
  Eigen::RowVector3d new_min_corner, new_max_corner;
  for (int i = 0; i < A.min_corner.cols(); i++) {
    new_min_corner(0, i) = std::min(A.min_corner(0, i), B.min_corner(0, i));
    new_max_corner(0, i) = std::max(A.max_corner(0, i), B.max_corner(0, i));
  }

  B.min_corner = new_min_corner;
  B.max_corner = new_max_corner;
}

