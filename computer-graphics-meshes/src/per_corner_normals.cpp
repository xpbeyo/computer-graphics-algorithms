#include "per_corner_normals.h"
#include "triangle_area_normal.h"
// Hint:
#include "vertex_triangle_adjacency.h"
#include <iostream>

void per_corner_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double corner_threshold,
  Eigen::MatrixXd & N)
{
  N.resize(F.rows() * 3, 3);
  std::vector<std::vector<int> > VF;
  vertex_triangle_adjacency(F, V.rows(), VF);
  for (int i = 0; i < F.rows(); i++) {
    Eigen::RowVector3d n_f = triangle_area_normal(
      V.row(F(i, 0)),
      V.row(F(i, 1)),
      V.row(F(i, 2))
    ).normalized();
    for (int j = 0; j < F.cols(); j++) {
      int c_i = F(i, j);
      Eigen::RowVector3d n(0, 0, 0);
      for (int k = 0; k < VF[c_i].size(); k++) {
        Eigen::RowVector3d n_g;
        n_g = triangle_area_normal(
          V.row(F(VF[c_i][k], 0)),
          V.row(F(VF[c_i][k], 1)),
          V.row(F(VF[c_i][k], 2))
        ).normalized();
        if (n_g.dot(n_f) > cos(corner_threshold * M_PI / 180.0)) {
          n = n + triangle_area_normal(
            V.row(F(VF[c_i][k], 0)),
            V.row(F(VF[c_i][k], 1)),
            V.row(F(VF[c_i][k], 2))
          );
        }
      }
      N.row(i * 3 + j) = n.normalized();
    }
  }
}
