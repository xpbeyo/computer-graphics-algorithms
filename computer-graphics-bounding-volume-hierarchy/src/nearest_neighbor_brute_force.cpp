#include "nearest_neighbor_brute_force.h"
#include <limits>// std::numeric_limits<double>::infinity();

void nearest_neighbor_brute_force(
  const Eigen::MatrixXd & points,
  const Eigen::RowVector3d & query,
  int & I,
  double & sqrD)
{
  double smallest = std::numeric_limits<double>::infinity();
  int smallest_i = -1;
  for (int i = 0; i < points.rows(); i++) {
    double dis = std::pow((points.row(i) - query).norm(), 2);
    if (dis < smallest) {
      smallest = dis;
      smallest_i = i;
    }
  }
  I = smallest_i;
  sqrD = smallest;
}
