// -----------------------------------------------------------------------------
// edit .setup/cpp/000-forward-declarations.cpp
// Ivan Jacob Agaloos Pesigan
// -----------------------------------------------------------------------------

#include <RcppArmadillo.h>
// [[Rcpp::depends(RcppArmadillo)]]

Rcpp::List KFilterLag1(const arma::mat& data, const arma::mat& Lambda,
                       const arma::mat& mu0, const arma::mat& Sigma0,
                       const arma::mat& beta, const arma::mat& chol_psi,
                       const arma::mat& chol_theta);
