#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"

bool raycolor(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb)
{
  int hit_id;
  double t;
  Eigen::Vector3d n;
  if (first_hit(ray, min_t, objects, hit_id, t, n)) {
    rgb = blinn_phong_shading(ray, hit_id, t, n, objects, lights);
    if (num_recursive_calls <= 2) {
      Ray reflection_ray;
      reflection_ray.origin = ray.origin + t * ray.direction;
      Eigen::Vector3d r = reflect(ray.direction.normalized(), n);
      reflection_ray.direction = r;
      Eigen::Vector3d temp_rgb;
      raycolor(reflection_ray, 0.0001, objects, lights, num_recursive_calls + 1, temp_rgb);
      rgb = rgb + (objects[hit_id]->material->km.array() * temp_rgb.array()).matrix();
    }
    return true;
  }
  rgb = Eigen::Vector3d(0,0,0);
  return false;
}
