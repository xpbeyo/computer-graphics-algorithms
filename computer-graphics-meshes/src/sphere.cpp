#include "sphere.h"
#include <iostream>

void sphere(
  const int num_faces_u,
  const int num_faces_v,
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{
  int num_vertices = (num_faces_u + 1) *  (num_faces_v + 1);
  int num_faces = num_faces_u * num_faces_v;
  V.resize(num_vertices, 3);
  F.resize(num_faces, 4);
  UV.resize(num_vertices, 2);
  UF.resize(num_faces, 4);
  NV.resize(num_vertices, 3);
  NF.resize(num_faces, 4);
  double unit_theta = M_PI / num_faces_v;
  double unit_phi = 2 * M_PI / num_faces_u;
  double r = 1.0;

  for (int i = 0; i < num_faces_u + 1; i++) {
    double phi = unit_phi * i;
    for (int j = 0; j < num_faces_v + 1; j++) {
      int v_index = i * (num_faces_v + 1) + j;
      double theta = unit_theta * j;
      double x = r * std::sin(phi) * std::sin(-theta); 
      double y = - r * std::cos(theta);
      double z = r * std::cos(phi) * std::sin(-theta);
      V.row(v_index) = Eigen::RowVector3d(x, y, z);
      UV.row(v_index) = Eigen::RowVector2d((double)i / (num_faces_u + 1), (double)j / (num_faces_v + 1));
      NV.row(v_index) = Eigen::RowVector3d(x, y, z).normalized();
    }
  }

  for (int i = 0; i < num_faces_u; i++) {
    for (int j = 0; j < num_faces_v; j++) {
      int f_index = i * num_faces_v + j;
      Eigen::RowVector4i face_indexes = Eigen::RowVector4i(
        i * (num_faces_v + 1) + j,
        (i + 1) * (num_faces_v + 1) + j,
        (i + 1) * (num_faces_v + 1) + j + 1,
        i * (num_faces_v + 1) + j + 1
      );
      F.row(f_index) = face_indexes;
      UF.row(f_index) = face_indexes;
      NF.row(f_index) = face_indexes;
    }
  }
}
