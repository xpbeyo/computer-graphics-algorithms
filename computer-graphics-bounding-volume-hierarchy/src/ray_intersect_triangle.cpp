#include "ray_intersect_triangle.h"
#include <Eigen/Dense>
#include <iostream>

bool ray_intersect_triangle(
  const Ray & ray,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  const double min_t,
  const double max_t,
  double & t)
{
  Eigen::Vector3d t1 = (A - B).transpose();
  Eigen::Vector3d t2 = (C - B).transpose();
  Eigen::Vector3d anchor = B.transpose();
  Eigen::Matrix<double, 3, 3> m;
  m << t1, t2, -ray.direction;
  if (m.determinant() == 0) {
    return false;
  }
  m = m.inverse().eval();
  Eigen::Vector3d result = m * (ray.origin - anchor);
  if (result[0] >= 0 
      && result[1] >= 0
      && result[0] + result[1] <= 1
      && result[2] >= min_t
      && result[2] <= max_t) 
  {
    t = result[2];
    return true;
  }
  return false;
}

