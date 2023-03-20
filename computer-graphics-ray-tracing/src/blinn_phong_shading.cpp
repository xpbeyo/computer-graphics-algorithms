#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>
#include <algorithm>

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id, 
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  // Create shorthand for the fields in Material
  const Eigen::Vector3d& ka = objects[hit_id]->material->ka;
  const Eigen::Vector3d& kd = objects[hit_id]->material->kd;
  const Eigen::Vector3d& ks = objects[hit_id]->material->ks;
  const double& phong_exponent = objects[hit_id]->material->phong_exponent;

  Eigen::Vector3d q = ray.origin + ray.direction * t;
  Eigen::Vector3d rgb = 0.1 * ka;

  for (int i = 0; i < lights.size(); i++) {
    // Create the shadow ray
    Ray shadow_ray;
    shadow_ray.origin = q;
    double max_t;
    lights[i]->direction(q, shadow_ray.direction, max_t);

    Eigen::Vector3d l = shadow_ray.direction;
    Eigen::Vector3d v = (-ray.direction).normalized();
    Eigen::Vector3d h = (v + l).normalized();

    // Test for intersection with other objects
    int shawdow_hit_id;
    double shadow_t;
    Eigen::Vector3d shadow_n;
    if (!first_hit(shadow_ray, 0.0001, objects, shawdow_hit_id, shadow_t, shadow_n) || shadow_t > max_t) {
      rgb = rgb 
        + (kd.array() * lights[i]->I.array()).matrix() * std::max(0.0, n.dot(l))
        + (ks.array() * lights[i]->I.array()).matrix() * std::pow(std::max(0.0, n.dot(h)), phong_exponent);
    }
  }
  return rgb;
}
