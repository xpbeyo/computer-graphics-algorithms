#include "triangle_triangle_intersection.h"
#include "ray_intersect_triangle.h"
#include <vector>
#include "Ray.h"

bool triangle_triangle_intersection(
  const Eigen::RowVector3d & A0,
  const Eigen::RowVector3d & A1,
  const Eigen::RowVector3d & A2,
  const Eigen::RowVector3d & B0,
  const Eigen::RowVector3d & B1,
  const Eigen::RowVector3d & B2)
{
  std::vector<Eigen::RowVector3d> A {A0, A1, A2};
  std::vector<Eigen::RowVector3d> B {B0, B1, B2};
  for (int i = 0; i < A.size(); i++) {
    Ray ray(A[i], A[(i + 1) % A.size()] - A[i]);
    double temp_t;
    if (ray_intersect_triangle(ray, B0, B1, B2, 0.0, 1.0, temp_t)) {
      return true;
    }
  }

  for (int i = 0; i < B.size(); i++) {
    Ray ray(B[i], B[(i + 1) % B.size()] - B[i]);
    double temp_t;
    if (ray_intersect_triangle(ray, A0, A1, A2, 0.0, 1.0, temp_t)) {
      return true;
    }
  }
  return false;
}
