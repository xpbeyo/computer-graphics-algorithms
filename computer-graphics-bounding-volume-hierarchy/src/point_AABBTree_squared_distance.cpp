#include "point_AABBTree_squared_distance.h"
#include "point_box_squared_distance.h"
#include <limits>
#include <queue> // std::priority_queue

bool point_AABBTree_squared_distance(
    const Eigen::RowVector3d & query,
    const std::shared_ptr<AABBTree> & root,
    const double min_sqrd,
    const double max_sqrd,
    double & sqrd,
    std::shared_ptr<Object> & descendant)
{
  typedef std::pair<double, std::shared_ptr<Object>> node;
  std::priority_queue<node, std::vector<node>, std::greater<node>> q;
  double d_r = point_box_squared_distance(query, root->box);
  node root_node = std::make_pair(d_r, root);
  q.push(root_node);
  double d = std::numeric_limits<double>::infinity();
  while (!q.empty()) {
    node this_node = q.top();
    q.pop();
    double d_s = this_node.first;
    std::shared_ptr<Object> this_obj = this_node.second;
    if (d_s < d) {
      std::shared_ptr<AABBTree> aabb = std::dynamic_pointer_cast<AABBTree>(this_obj);
      if (aabb) {
        double d_l = point_box_squared_distance(query, aabb->left->box);
        q.push(std::make_pair(d_l, aabb->left));
        double d_r = point_box_squared_distance(query, aabb->right->box);
        q.push(std::make_pair(d_r, aabb->right));
      }
      else {
        double temp_d;
        std::shared_ptr<Object> _;
        this_obj->point_squared_distance(query, min_sqrd, max_sqrd, temp_d, _);
        if (temp_d < d) {
          d = temp_d;
          descendant = this_obj;
        }
      }
    }
  }
  sqrd = d;
  return (min_sqrd <= d && d <= max_sqrd);
}
