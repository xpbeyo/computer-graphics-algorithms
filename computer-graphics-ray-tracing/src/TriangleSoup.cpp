#include "TriangleSoup.h"
#include "Ray.h"
// Hint
#include "first_hit.h"

bool TriangleSoup::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  double temp_t;
  Eigen::Vector3d temp_n;
  int temp_hit_id;
  if (first_hit(ray, min_t, this->triangles, temp_hit_id, t, n)) {
    t = temp_t;
    n = temp_n;
    return true;
  }
  return false;
}



