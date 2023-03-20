#include "Plane.h"
#include "Ray.h"
bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  double denominator = this->normal.dot(ray.direction);
  if (denominator == 0) {
    return false;
  }

  double numerator = -this->normal.dot(ray.origin - this->point);
  double temp_t = numerator / denominator;
  if (temp_t >= min_t) {
    t = temp_t;
    n = this->normal.normalized();
    return true;
  }
  return false;
}

