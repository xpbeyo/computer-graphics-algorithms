#include "Sphere.h"
#include "Ray.h"
#include "math.h"
#include <vector>
bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  double a = ray.direction.dot(ray.direction);
  double b = 2 * ray.direction.dot(ray.origin - this->center);
  double c = (ray.origin - this->center).dot(ray.origin - this->center) - std::pow(this->radius, 2);

  double delta = std::pow(b, 2) - 4 * a * c;
  if (delta < 0) {
    return false;
  }

  else {
    double t1 = (-b + std::sqrt(delta)) / (2 * a);
    double t2 = (-b - std::sqrt(delta)) / (2 * a);
    std::vector<double> roots;
    if (t1 >= min_t) {
      roots.push_back(t1);
    }

    if (t2 >= min_t) {
      roots.push_back(t2);
    }

    if (roots.size() > 0) {
      t = *std::min_element(roots.begin(), roots.end());
      n = (ray.origin + t * ray.direction - this->center).normalized();
      return true;
    }

    return false;
  }
}

