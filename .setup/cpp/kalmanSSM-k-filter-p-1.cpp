// -----------------------------------------------------------------------------
// edit .setup/cpp/kalmanSSM-k-filter-lag-1.cpp
// Ivan Jacob Agaloos Pesigan
// -----------------------------------------------------------------------------

#include <RcppArmadillo.h>
// [[Rcpp::depends(RcppArmadillo)]]

//' Kalman Filter with Lag 1 for State Space Models
//'
//' @author Ivan Jacob Agaloos Pesigan
//'
//' @details The measurement model is given by
//'   \deqn{
//'     \mathbf{y}_{t}
//'     =
//'     \boldsymbol{\nu}
//'     +
//'     \boldsymbol{\Lambda}
//'     \boldsymbol{\eta}_{t}
//'     +
//'     \boldsymbol{\varepsilon}_{t}
//'     \quad
//'     \mathrm{with}
//'     \quad
//'     \boldsymbol{\varepsilon}_{t}
//'     \sim
//'     \mathcal{N}
//'     \left(
//'     \mathbf{0},
//'     \boldsymbol{\Theta}
//'     \right)
//'   }
//'   where \eqn{\mathbf{y}}, \eqn{\boldsymbol{\eta}},
//'   and \eqn{\boldsymbol{\varepsilon}}
//'   are random variables and \eqn{\boldsymbol{\nu}},
//'   \eqn{\boldsymbol{\Lambda}},
//'   and \eqn{\boldsymbol{\Theta}} are model parameters.
//'   \eqn{\mathbf{y}} is a vector of observed random variables,
//'   \eqn{\boldsymbol{\eta}} is a vector of latent random variables,
//'   and \eqn{\boldsymbol{\varepsilon}}
//'   is a vector of random measurement errors
//'   while \eqn{\boldsymbol{\nu}} is a vector of intercept,
//'   \eqn{\boldsymbol{\Lambda}} is a matrix of factor loadings,
//'   and \eqn{\boldsymbol{\Theta}} is the covariance matrix of
//'   \eqn{\boldsymbol{\varepsilon}}.
//'
//'   The dynamic structure is given by
//'   \deqn{
//'     \boldsymbol{\eta}_{t}
//'     =
//'     \boldsymbol{\alpha}
//'     +
//'     \boldsymbol{\beta}
//'     \boldsymbol{\eta}_{t - 1}
//'     +
//'     \boldsymbol{\zeta}_{t}
//'     \quad
//'     \mathrm{with}
//'     \quad
//'     \boldsymbol{\zeta}_{t}
//'     \sim
//'     \mathcal{N}
//'     \left(
//'     \mathbf{0},
//'     \boldsymbol{\Psi}
//'     \right)
//'   }
//'   where \eqn{\boldsymbol{\eta}_{t}}, \eqn{\boldsymbol{\eta}_{l}},
//'   and \eqn{\boldsymbol{\zeta}_{t}} are random variables
//'   and \eqn{\boldsymbol{\alpha}}, \eqn{\boldsymbol{\beta}},
//'   and \eqn{\boldsymbol{\Psi}} are model parameters.
//'   \eqn{\boldsymbol{\eta}_{t}} is a vector of latent variables
//'   at time \eqn{t}, \eqn{\boldsymbol{\eta}_{t - 1}}
//'   is a vector of latent variables at
//'   \eqn{t - 1},
//'   and \eqn{\boldsymbol{\zeta}_{t}} is a vector of dynamic noise
//'   at time \eqn{t} while \eqn{\boldsymbol{\alpha}}
//'   is a vector of intercepts,
//'   \eqn{\boldsymbol{\beta}} is a matrix of autoregression
//'   and cross regression coefficients,
//'   and \eqn{\boldsymbol{\Psi}} is the covariance matrix of
//'   \eqn{\boldsymbol{\zeta}_{t}}.
//'
//' @param data Numeric matrix.
//'   `time` by `k` data matrix.
//' @param Lambda Numeric matrix.
//'   Measurement or observation matrix.
//' @param mu0 Numeric matrix.
//'   Initial state mean vector
//'   where `p` is the number of lags.
//' @param Sigma0 Numeric matrix.
//'   Initial state covariance matrix
//'   where `p` is the number of lags.
//' @param beta Numeric matrix.
//'   State transition matrix.
//' @param chol_psi Numeric matrix.
//'   Cholesky decomposition of the state error covariance matrix Psi.
//' @param chol_theta Numeric matrix.
//'   Cholesky decomposition of the  observation error covariance matrix Theta.
//'
//' @return List of filtered state variables and other Kalman filter results.
//'
//' @examples
//' data <- dat_univ_p1[, "y", drop = FALSE]
//' kalman <- KFilterP1(
//'   data = data,
//'   Lambda = matrix(1),
//'   mu0 = matrix(0),
//'   Sigma0 = matrix(1),
//'   beta = matrix(0.8),
//'   chol_psi = matrix(1),
//'   chol_theta = matrix(1)
//' )
//' str(kalman)
//'
//' data <- dat_multiv_p1[, c("y1", "y2"), drop = FALSE]
//' kalman <- KFilterP1(
//'   data = data,
//'   Lambda = diag(2),
//'   mu0 = matrix(data = 0, nrow = 2),
//'   Sigma0 = diag(2),
//'   beta = diag(x = 0.8, nrow = 2, ncol = 2),
//'   chol_psi = chol(diag(2)),
//'   chol_theta = chol(diag(2))
//' )
//' str(kalman)
//'
//' @family Kalman Filter for State Space Models Functions
//' @keywords kalmanSSM kalman
//' @export
// [[Rcpp::export]]
Rcpp::List KFilterP1(const arma::mat& data, const arma::mat& Lambda,
                     const arma::mat& mu0, const arma::mat& Sigma0,
                     const arma::mat& beta, const arma::mat& chol_psi,
                     const arma::mat& chol_theta) {
  // Step 1: Initialize variables and matrices to store filter results
  arma::mat Psi = chol_psi.t() * chol_psi;
  arma::mat Theta = chol_theta.t() * chol_theta;
  int time = data.n_rows;
  int k = data.n_cols;
  int j = beta.n_rows;
  arma::cube x_predicted(j, 1, time);
  arma::cube x_cov_predicted(j, j, time);
  arma::cube x_filtered(j, 1, time);
  arma::cube x_cov_filtered(j, j, time);
  arma::cube innovations(k, 1, time);
  arma::cube sigma_innovations(k, k, time);

  // Step 2: Initialize state variables at time 0
  arma::mat x_0 = mu0;
  arma::mat x_cov_0 = Sigma0;
  x_predicted.slice(0) = beta * x_0;
  x_cov_predicted.slice(0) = beta * x_cov_0 * beta.t() + Psi;

  // Step 3: Compute initial innovation statistics
  arma::mat sigma_innovations_temp =
      Lambda * x_cov_predicted.slice(0) * Lambda.t() + Theta;
  sigma_innovations.slice(0) =
      (sigma_innovations_temp.t() + sigma_innovations_temp) / 2.0;
  arma::mat sigma_innovations_inv = arma::inv(sigma_innovations.slice(0));
  arma::mat gain =
      x_cov_predicted.slice(0) * Lambda.t() * sigma_innovations_inv;
  innovations.slice(0) = data.row(0).t() - Lambda * x_predicted.slice(0);
  x_filtered.slice(0) = x_predicted.slice(0) + gain * innovations.slice(0);
  x_cov_filtered.slice(0) =
      x_cov_predicted.slice(0) - gain * Lambda * x_cov_predicted.slice(0);

  // Step 4: Initialize negative log-likelihood
  arma::mat sigma_innovations_mat = sigma_innovations.slice(0);
  double neg_log_like =
      log(arma::det(sigma_innovations_mat)) +
      arma::as_scalar(innovations.slice(0).t() * sigma_innovations_inv *
                      innovations.slice(0));

  // Step 5: Loop through time steps for filtering
  for (int i = 1; i < time; ++i) {
    // Predict step
    x_predicted.slice(i) = beta * x_filtered.slice(i - 1);
    x_cov_predicted.slice(i) =
        beta * x_cov_filtered.slice(i - 1) * beta.t() + Psi;

    // Compute innovation statistics
    sigma_innovations_temp =
        Lambda * x_cov_predicted.slice(i) * Lambda.t() + Theta;
    sigma_innovations.slice(i) =
        (sigma_innovations_temp.t() + sigma_innovations_temp) / 2.0;
    sigma_innovations_inv = arma::inv(sigma_innovations.slice(i));
    gain = x_cov_predicted.slice(i) * Lambda.t() * sigma_innovations_inv;

    // Update step
    innovations.slice(i) = data.row(i).t() - Lambda * x_predicted.slice(i);
    x_filtered.slice(i) = x_predicted.slice(i) + gain * innovations.slice(i);
    x_cov_filtered.slice(i) =
        x_cov_predicted.slice(i) - gain * Lambda * x_cov_predicted.slice(i);

    // Update negative log-likelihood
    sigma_innovations_mat = sigma_innovations.slice(i);
    neg_log_like +=
        log(arma::det(sigma_innovations_mat)) +
        arma::as_scalar(innovations.slice(i).t() * sigma_innovations_inv *
                        innovations.slice(i));
  }

  // Step 6: Multiply the negative log-likelihood by 0.5
  neg_log_like *= 0.5;

  // Step 7: Return a list of filtered state variables and other filter results
  return Rcpp::List::create(
      Rcpp::Named("x_predicted") = x_predicted,
      Rcpp::Named("x_cov_predicted") = x_cov_predicted,
      Rcpp::Named("x_filtered") = x_filtered,
      Rcpp::Named("x_cov_filtered") = x_cov_filtered,
      Rcpp::Named("neg_log_like") = neg_log_like,
      Rcpp::Named("innovations") = innovations,
      Rcpp::Named("sigma_innovations") = sigma_innovations,
      Rcpp::Named("gain") = gain);
}
