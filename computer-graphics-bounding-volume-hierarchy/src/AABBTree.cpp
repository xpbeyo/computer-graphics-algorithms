#include "AABBTree.h"
#include "insert_box_into_box.h"

AABBTree::AABBTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth): 
  depth(std::move(a_depth)), 
  num_leaves(objects.size())
{
  int max_axis;
  double max_distance = -std::numeric_limits<double>::infinity();
  for (int i = 0; i < objects.size(); i++) {
    insert_box_into_box(objects[i]->box, this->box);
  }
  for (int i = 0; i < this->box.min_corner.cols(); i++) {
    double temp_distance = this->box.max_corner(0, i) - this->box.min_corner(0, i);
    if (temp_distance > max_distance) {
      max_axis = i;
      max_distance = temp_distance;
    }
  }
  double m = (this->box.max_corner(0, max_axis) + this->box.min_corner(0, max_axis)) / 2.0;
  std::vector<std::shared_ptr<Object> > left_objects{};
  std::vector<std::shared_ptr<Object> > right_objects{};
  for (int i = 0; i < objects.size(); i++) {
    if (objects[i]->box.center()(0, max_axis) <= m) {
      left_objects.push_back(objects[i]);
    }
    else {
      right_objects.push_back(objects[i]);
    }
  }

  if (left_objects.size() == 0) {
    left_objects.push_back(right_objects.back());
    right_objects.pop_back();
  }

  if (right_objects.size() == 0) {
    right_objects.push_back(left_objects.back());
    left_objects.pop_back();
  }

  if (left_objects.size() == 0) {
    this->left = nullptr;
  }
  else if (left_objects.size() == 1) {
    this->left = left_objects[0];
  }
  else {
    this->left = std::make_shared<AABBTree>(left_objects, depth + 1);
  }
  if (right_objects.size() == 0) {
    this->right = nullptr;
  }
  else if (right_objects.size() == 1) {
    this->right = right_objects[0];
  }
  else {
    this->right = std::make_shared<AABBTree>(right_objects, depth + 1);
  }
}
