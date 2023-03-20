#include "point_box_squared_distance.h"

double point_box_squared_distance(
  const Eigen::RowVector3d & query,
  const BoundingBox & box)
{
  Eigen::RowVector3d min_dif;
  for (int i = 0; i < box.max_corner.cols(); i++) {
    min_dif(0, i) = std::max(
      std::max(box.min_corner(0, i) - query(0, i),  query(0, i) - box.max_corner(0, i)), 0.0);
  }
  return std::pow(min_dif.norm(), 2);
}
