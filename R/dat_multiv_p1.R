#' Data from a Multivariate State Space Model (p = 1)
#'
#' @format A matrix with 100 rows (time points) and 5 columns
#'   (`eta1`, and `eta2` for latent states,
#'   `y1`, and `y2` for observed data,
#'   and
#'   `time` for discrete time from 1 to 100)
#'   generated from the state space model given by
#'   \deqn{
#'     \left(\begin{array}{c} y_{1_{t}} \\ y_{2_{t}} \end{array} \right)
#'     =
#'     \left(\begin{array}{c} \eta_{1_{t}} \\ \eta_{2_{t}} \end{array} \right)
#'     +
#'     \left(
#'       \begin{array}{c} \varepsilon{1_{t}} \\ \varepsilon{2_{t}} \end{array}
#'     \right)
#'     \quad
#'     \text{with}
#'     \quad
#'     \left(
#'       \begin{array}{c} \varepsilon_{1_{t}} \\ \varepsilon_{2_{t}} \end{array}
#'     \right)
#'     \sim
#'     \mathcal{N}
#'     \left(
#'     \left(\begin{array}{c} 0 \\ 0 \end{array} \right) ,
#'     \left(\begin{array}{cc} 1 & 0.0 \\ 0.0 & 1 \end{array} \right)
#'     \right)
#'   }
#'   \deqn{
#'     \left(\begin{array}{c} \eta_{1_{t}} \\ \eta_{2_{t}} \end{array} \right)
#'     =
#'     \left(\begin{array}{cc} 0.8 & 0.0 \\ 0.0 & 0.8 \end{array} \right)
#'     \left(
#'       \begin{array}{c} \eta_{1_{t - 1}} \\ \eta_{2_{t - 1}} \end{array}
#'     \right)
#'     +
#'     \left(\begin{array}{c} \zeta_{1_{t}} \\ \zeta_{2_{t}} \end{array} \right)
#'     \quad
#'     \text{with}
#'     \quad
#'     \left(\begin{array}{c} \zeta{1_{t}} \\ \zeta{2_{t}} \end{array} \right)
#'     \sim
#'     \mathcal{N}
#'     \left(
#'     \left(\begin{array}{c} 0 \\ 0 \end{array} \right) ,
#'     \left(\begin{array}{cc} 1 & 0.0 \\ 0.0 & 1 \end{array} \right)
#'     \right)
#'   }
#' @keywords kalmanSSM data
"dat_multiv_p1"
