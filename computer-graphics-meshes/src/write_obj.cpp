#include "write_obj.h"
#include <fstream>
#include <cassert>
#include <iostream>

void write_vertices(
  std::ofstream & object_file,
  const std::string type,
  const Eigen::MatrixXd & vertices)
{
  for (int i = 0; i < vertices.rows(); i++) {
    object_file << type << " "; 
    for (int j = 0; j < vertices.cols(); j++) {
      object_file << vertices(i, j) << " ";
    }
    object_file << std::endl;
  }
}

void write_faces(
  std::ofstream & object_file,
  const Eigen::MatrixXi & F,
  const Eigen::MatrixXi & UF,
  const Eigen::MatrixXi & NF)
{
  for (int i = 0; i < F.rows(); i++) {
    object_file << "f ";
    for (int j = 0; j < F.cols(); j++) {
      object_file << F(i, j) + 1 << "/";
      object_file << UF(i, j) + 1 << "/";
      object_file << NF(i, j) + 1 << " ";
    }
    object_file << std::endl;
  }
} 

bool write_obj(
  const std::string & filename,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const Eigen::MatrixXd & UV,
  const Eigen::MatrixXi & UF,
  const Eigen::MatrixXd & NV,
  const Eigen::MatrixXi & NF)
{
  assert((F.size() == 0 || F.cols() == 3 || F.cols() == 4) && "F must have 3 or 4 columns");
  assert(F.rows() == UF.rows() && UF.rows() == NF.rows());
  assert(F.cols() == UF.cols() && UF.cols() == NF.cols());
  std::ofstream object_file;
  object_file.open(filename);
  if (!object_file.is_open()) {
    return false;
  }
  write_vertices(object_file, "v", V);
  write_vertices(object_file, "vt", UV);
  write_vertices(object_file, "vn", NV);
  write_faces(object_file, F, UF, NF);
  
  object_file.close();

  return true;
}
