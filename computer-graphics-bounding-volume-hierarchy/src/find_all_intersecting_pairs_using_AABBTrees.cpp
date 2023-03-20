#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "box_box_intersect.h"
// Hint: use a list as a queue
#include <list> 

void find_all_intersecting_pairs_using_AABBTrees(
  const std::shared_ptr<AABBTree> & rootA,
  const std::shared_ptr<AABBTree> & rootB,
  std::vector<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > > & 
    leaf_pairs)
{
  std::list<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > > Q;
  if (box_box_intersect(rootA->box, rootB->box)) {
    Q.push_back(std::make_pair(rootA, rootB));
  }

  while (!Q.empty()) {
    std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > this_node = Q.front();
    Q.pop_front();
    std::shared_ptr<Object> node_a, node_b;
    node_a = this_node.first;
    node_b = this_node.second;
    std::shared_ptr<AABBTree> aabb_a, aabb_b;
    aabb_a = std::dynamic_pointer_cast<AABBTree>(node_a);
    aabb_b = std::dynamic_pointer_cast<AABBTree>(node_b);

    if (!aabb_a && !aabb_b) {
      leaf_pairs.push_back(std::make_pair(node_a, node_b));
    }
    else if (!aabb_a) {
      if (box_box_intersect(node_a->box, aabb_b->left->box)) {
        Q.push_back(std::make_pair(node_a, aabb_b->left));
      }
      if (box_box_intersect(node_a->box, aabb_b->right->box)) {
        Q.push_back(std::make_pair(node_a, aabb_b->right));
      }
    }
    else if (!aabb_b) {
      if (box_box_intersect(aabb_a->left->box, node_b->box)) {
        Q.push_back(std::make_pair(aabb_a->left, node_b));
      }
      if (box_box_intersect(aabb_a->right->box, node_b->box)) {
        Q.push_back(std::make_pair(aabb_a->right, node_b));
      }
    }
    else {
      if (box_box_intersect(aabb_a->left->box, aabb_b->left->box)) {
        Q.push_back(std::make_pair(aabb_a->left, aabb_b->left));
      }
      if (box_box_intersect(aabb_a->left->box, aabb_b->right->box)) {
        Q.push_back(std::make_pair(aabb_a->left, aabb_b->right));
      }
      if (box_box_intersect(aabb_a->right->box, aabb_b->left->box)) {
        Q.push_back(std::make_pair(aabb_a->right, aabb_b->left));
      }
      if (box_box_intersect(aabb_a->right->box, aabb_b->right->box)) {
        Q.push_back(std::make_pair(aabb_a->right, aabb_b->right));
      }
    }
  }

}
