#include "insert_triangle_into_box.h"
#include <vector>
#include <algorithm>
void insert_triangle_into_box(
  const Eigen::RowVector3d & a,
  const Eigen::RowVector3d & b,
  const Eigen::RowVector3d & c,
  BoundingBox & B)
{
  Eigen::RowVector3d mins, maxes;
  for (int i = 0; i < a.cols(); i++) {
    std::vector<double> temp_min = {B.min_corner(0, i), a(0, i), b(0, i), c(0, i)};
    std::vector<double> temp_max = {B.max_corner(0, i), a(0, i), b(0, i), c(0, i)};

    mins(0, i) = *std::min_element(temp_min.begin(), temp_min.end());
    maxes(0, i) = *std::max_element(temp_max.begin(), temp_max.end());
  }

  B.min_corner = mins;
  B.max_corner = maxes;
}
