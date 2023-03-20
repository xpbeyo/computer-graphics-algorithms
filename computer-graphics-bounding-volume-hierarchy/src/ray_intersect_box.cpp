#include "ray_intersect_box.h"
#include <vector>
#include <algorithm>

bool ray_intersect_box(
  const Ray & ray,
  const BoundingBox& box,
  const double min_t,
  const double max_t)
{
  const double& x_min = box.min_corner(0, 0);
  const double& x_max = box.max_corner(0, 0);
  const double& y_min = box.min_corner(0, 1);
  const double& y_max = box.max_corner(0, 1);
  const double& z_min = box.min_corner(0, 2);
  const double& z_max = box.max_corner(0, 2);

  const double& x_e = ray.origin(0, 0);
  const double& y_e = ray.origin(1, 0);
  const double& z_e = ray.origin(2, 0);

  double t_x_min, t_x_max;
  double t_y_min, t_y_max;
  double t_z_min, t_z_max;

  double a = 1 / ray.direction(0, 0);
  if (a >= 0) {
    t_x_min = a * (x_min - x_e);
    t_x_max = a * (x_max - x_e);
  }

  else {
    t_x_min = a * (x_max - x_e);
    t_x_max = a * (x_min - x_e);
  }

  a = 1 / ray.direction(1, 0);
  if (a >= 0) {
    t_y_min = a * (y_min - y_e);
    t_y_max = a * (y_max - y_e);
  }
  else {
    t_y_min = a * (y_max - y_e);
    t_y_max = a * (y_min - y_e);
  }

  a = 1 / ray.direction(2, 0);
  if (a >= 0) {
    t_z_min = a * (z_min - z_e);
    t_z_max = a * (z_max - z_e);
  }
  else {
    t_z_min = a * (z_max - z_e);
    t_z_max = a * (z_min - z_e);
  }

  std::vector<double> mins = { t_x_min, t_y_min, t_z_min };
  std::vector<double> maxes = { t_x_max, t_y_max, t_z_max };

  double max_mins = *std::max_element(mins.begin(), mins.end());
  double min_maxes = *std::min_element(maxes.begin(), maxes.end());

  if (max_mins <= min_maxes) {
    if (min_t <= max_mins || min_maxes <= max_t) {
      return true;
    }
  }
  return false;
}
