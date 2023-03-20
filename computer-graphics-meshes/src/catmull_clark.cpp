#include "catmull_clark.h"
#include <unordered_map>
#include <utility>
#include <functional>
#include "vertex_triangle_adjacency.h"
#include <vector>
#include <set>

// Reference
// https://www.techiedelight.com/use-std-pair-key-std-unordered_map-cpp/
typedef std::pair<int, int> edge;
 
struct edge_hash
{
  template <class T1, class T2>
  std::size_t operator() (const std::pair<T1, T2> &pair) const
  {
    return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
  }
};

int find_or_insert(
  std::vector<Eigen::RowVector3d> & SVertices,
  const Eigen::RowVector3d & target
) {
  auto it = std::find(SVertices.begin(), SVertices.end(), target);
  if (it == SVertices.end()) {
    SVertices.push_back(target);
    return SVertices.size() - 1;
  }
  return std::distance(SVertices.begin(), it);
}

Eigen::RowVector3d avg_vector(
  const std::set<int> & indices,
  const std::vector<Eigen::RowVector3d> & vertices) 
{
  Eigen::RowVector3d init(0, 0, 0);
  for (auto i: indices) {
    init += vertices[i];
  }
  return init / (double)indices.size();
}

Eigen::RowVector3d avg_vector(
  const std::set<int> & indices,
  const Eigen::MatrixXd & vertices) 
{
  Eigen::RowVector3d init(0, 0, 0);
  for (auto i: indices) {
    init += vertices.row(i);
  }
  return init / (double)indices.size();
}

void catmull_clark(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const int num_iters,
  Eigen::MatrixXd & SV,
  Eigen::MatrixXi & SF)
{
  if (num_iters > 0) {

    std::vector<std::vector<int> > NF;
    vertex_triangle_adjacency(F, V.rows(), NF);
    std::vector<Eigen::RowVector3d> SVertices;
    std::vector<Eigen::RowVector4i> SFaces;
    std::unordered_map<edge, std::vector<int>, edge_hash > edge_face;
    std::unordered_map<int, int> F_face;
    std::unordered_map< int, std::vector<int> > F_edge;
    std::unordered_map< int, std::vector<int> > F_new_edge;


    for (int i = 0; i < F.rows(); i++) {

      F_edge[i] = std::vector<int>(F.cols());

      std::set<int> corners;
      for (int k = 0; k < F.cols(); k++) {
        corners.insert(F(i, k));
        int head, tail;
        head = F(i, k);
        tail = F(i, (k + 1) % F.cols());
        if (head > tail) {
          std::swap(head, tail);
        }
        edge this_edge = std::make_pair(head, tail);
        F_edge[i][k] = find_or_insert(
          SVertices, 
          (V.row(head) + V.row(tail)) / 2
        );
        
        if (edge_face.find(this_edge) == edge_face.end()) {
          edge_face[this_edge] = std::vector<int>();
        }

        edge_face[std::make_pair(head, tail)].push_back(i);

      }
      Eigen::RowVector3d face_average = avg_vector(corners, V);
      F_face[i] = find_or_insert(SVertices, face_average);
    }

    for (int i = 0; i < F.rows(); i++) {
      F_new_edge[i] = std::vector<int>(F.cols());
      for (int k = 0; k < F.cols(); k++) {
        int head, tail;
        head = F(i, k);
        tail = F(i, (k + 1) % F.cols());
        if (head > tail) {
          std::swap(head, tail);
        }
        edge this_edge = std::make_pair(head, tail);

        F_new_edge[i][k] = find_or_insert(
          SVertices,
          (
            SVertices[F_face[edge_face[this_edge][0]]] +
            SVertices[F_face[edge_face[this_edge][1]]] +
            V.row(head) +
            V.row(tail)
          ) / 4.0
        );
      }
    }

    for (int i = 0; i < NF.size(); i++) {
      Eigen::RowVector3d p = V.row(i);
      std::set<int> face_indices;
      std::set<int> edge_indices;
      for (int j = 0; j < NF[i].size(); j++) {
        int face_i = NF[i][j];
        face_indices.insert(F_face[face_i]);
        std::vector<int> local_edge_indices = F_edge[face_i];
        
        int p_index;
        for (int k = 0; k < F.cols(); k++) {
          if (V.row(F(face_i, k)) == p) {
            p_index = k;
            break;
          }
        }

        edge_indices.insert(local_edge_indices[(p_index + 3) % F.cols()]);
        edge_indices.insert(local_edge_indices[p_index]);
      }

      double n = (double)edge_indices.size();
      Eigen::RowVector3d new_p = (
        avg_vector(face_indices, SVertices) + 
        2 * avg_vector(edge_indices, SVertices) + 
        (n - 3) * p
      ) / n;
      SVertices.push_back(new_p);
      int new_p_i = SVertices.size() - 1;

      for (int j = 0; j < NF[i].size(); j++) {
        int face_i = NF[i][j];
        int p_index;
        for (int k = 0; k < F.cols(); k++) {
          if (V.row(F(face_i, k)) == p) {
            p_index = k;
            break;
          }
        }
        std::vector<int> new_edge_indices = F_new_edge[face_i];

        SFaces.push_back(Eigen::RowVector4i(
          new_edge_indices[(p_index + 3) % F.cols()],
          new_p_i,
          new_edge_indices[p_index],
          F_face[face_i]
        ));
      }
    }

    SV.resize(SVertices.size(), 3);
    SF.resize(SFaces.size(), 4);
    for (int i = 0; i < SVertices.size(); i++) {
      SV.row(i) = SVertices[i];
    }

    for (int i = 0; i < SFaces.size(); i++) {
      SF.row(i) = SFaces[i];
    }

    catmull_clark(SV, SF, num_iters - 1, SV, SF);
  }
  else {
    SV = V;
    SF = F;
  }
}
