#include "fast_mass_springs_precomputation_sparse.h"
#include "signed_incidence_matrix_sparse.h"
#include <vector>

bool fast_mass_springs_precomputation_sparse(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & E,
  const double k,
  const Eigen::VectorXd & m,
  const Eigen::VectorXi & b,
  const double delta_t,
  Eigen::VectorXd & r,
  Eigen::SparseMatrix<double>  & M,
  Eigen::SparseMatrix<double>  & A,
  Eigen::SparseMatrix<double>  & C,
  Eigen::SimplicialLLT<Eigen::SparseMatrix<double> > & prefactorization)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code

  const int n = V.rows();

  r.resize(E.rows());
  for (int i = 0; i < E.rows(); i++) {
    r[i] = (V.row(E(i, 0)) - V.row(E(i, 1))).norm();
  }
  std::vector<Eigen::Triplet<double> > M_ijv;
  for (int i = 0;i < n;i++) {
    M_ijv.emplace_back(i, i, m[i]);
  }
  M.resize(n, n);
  M.setFromTriplets(M_ijv.begin(), M_ijv.end());

  std::vector<Eigen::Triplet<double> > C_ijk;
  for (int i = 0; i < b.size(); i++) {
    C_ijk.emplace_back(i, b[i], 1);
  }
  C.resize(b.size(), n);
  C.setFromTriplets(C_ijk.begin(), C_ijk.end());

  signed_incidence_matrix_sparse(n, E, A);

  Eigen::SparseMatrix<double> Q(n, n);
  double w = 1e10;
  Q = k * A.transpose() * A + (1 / pow(delta_t, 2)) * M + w * C.transpose() * C;
  /////////////////////////////////////////////////////////////////////////////
  prefactorization.compute(Q);
  return prefactorization.info() != Eigen::NumericalIssue;
}
