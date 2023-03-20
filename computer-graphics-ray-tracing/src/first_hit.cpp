#include "first_hit.h"

bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id, 
  double & t,
  Eigen::Vector3d & n)
{
  if (objects.size() == 0) {
    return false;
  }

  double cur_t;
  Eigen::Vector3d cur_n;
  int cur_i;
  bool found = false;

  for (int i = 0; i < objects.size(); i++) {
    double temp_t;
    Eigen::Vector3d temp_n;
    if (objects[i]->intersect(ray, min_t, temp_t, temp_n)) {
      if (!found) {
        cur_t = temp_t;
        cur_n = temp_n;
        cur_i = i;
        found = true;
      }

      else if (temp_t < cur_t){
        cur_t = temp_t;
        cur_n = temp_n;
        cur_i = i;
      }
    }
  }

  if (found) {
    hit_id = cur_i;
    t = cur_t;
    n = cur_n;
    return true;
  }
  
  return false;
}

