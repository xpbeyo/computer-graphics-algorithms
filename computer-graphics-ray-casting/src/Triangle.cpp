#include "Triangle.h"
#include "Ray.h"
#include <Eigen/Dense>

bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  Eigen::Vector3d anchor, t1, t2;
  anchor = std::get<0>(this->corners);
  t1 = std::get<1>(this->corners) - std::get<0>(this->corners);
  t2 = std::get<2>(this->corners) - std::get<0>(this->corners);
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
      && result[2] >= min_t) 
  {
    t = result[2];
    n = t1.cross(t2).normalized();
    return true;
  }
  return false;

}


