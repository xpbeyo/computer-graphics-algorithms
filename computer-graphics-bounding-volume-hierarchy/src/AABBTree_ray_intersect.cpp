#include "AABBTree.h"
#include "ray_intersect_box.h"
#include <limits>
// See AABBTree.h for API
bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const 
{
  bool left_hit, right_hit;
  left_hit = false;
  right_hit = false;
  double left_t, right_t;
  std::shared_ptr<Object> left_desc, right_desc;
  if (this->left && ray_intersect_box(ray, this->left->box, min_t, max_t)) {
    left_hit = (this->left->ray_intersect(ray, min_t, max_t, left_t, left_desc));
    if (!left_desc) {
      left_desc = this->left;
    }
  }
  if (this->right && ray_intersect_box(ray, this->right->box, min_t, max_t)) {
    right_hit = (this->right->ray_intersect(ray, min_t, max_t, right_t, right_desc));
    if (!right_desc) {
      right_desc = this->right;
    }
    
  }

  if (left_hit && right_hit) {
    if (left_t <= right_t) {
      t = left_t;
      descendant = left_desc;
    }
    else {
      t = right_t;
      descendant = right_desc;
    }
  }
  else if (left_hit) {
    t = left_t;
    descendant = left_desc;
  }
  else if (right_hit) {
    t = right_t;
    descendant = right_desc;
  }
  else {
    return false;
  }
  return true;
}

