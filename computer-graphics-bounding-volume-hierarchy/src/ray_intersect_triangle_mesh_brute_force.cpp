#include "ray_intersect_triangle_mesh_brute_force.h"
#include "ray_intersect_triangle.h"
#include <limits>

bool ray_intersect_triangle_mesh_brute_force(
  const Ray & ray,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double min_t,
  const double max_t,
  double & hit_t,
  int & hit_f)
{
  double t = std::numeric_limits<double>::infinity();
  int f;
  for (int i = 0; i < F.rows(); i++) {
    double temp_t;
    if (ray_intersect_triangle(
      ray,
      V.row(F(i, 0)),
      V.row(F(i, 1)),
      V.row(F(i, 2)),
      min_t,
      max_t,
      temp_t
    )) {
      if (temp_t >= min_t && temp_t <= max_t && temp_t < t) {
        t = temp_t;
        f = i;
      }
    }
  }
  
  if (t != std::numeric_limits<double>::infinity()) {
    hit_t = t;
    hit_f = f;
    return true;
  }
  hit_t = 0;
  hit_f = 0;
  return false;
}
