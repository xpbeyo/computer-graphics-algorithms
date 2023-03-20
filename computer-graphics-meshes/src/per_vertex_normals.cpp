#include "per_vertex_normals.h"
#include "triangle_area_normal.h"
#include <vector>
#include <map>

void per_vertex_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  Eigen::MatrixXd & N)
{
  N.resize(V.rows(), 3);
  std::vector< std::vector<int> > V_F(V.rows());
  for (int i = 0; i < F.rows(); i++) {
    for (int j = 0; j < 3; j++) {
      V_F[F(i, j)].push_back(i);
    }
  }
  for (int i = 0; i < V_F.size(); i++) {
    Eigen::RowVector3d n(0, 0, 0);
    for (int j = 0; j < V_F[i].size(); j++) {
      n = n + triangle_area_normal(
        V.row(F(V_F[i][j], 0)),
        V.row(F(V_F[i][j], 1)),
        V.row(F(V_F[i][j], 2))
      );
    }
    N.row(i) = n.normalized();
  }
}
