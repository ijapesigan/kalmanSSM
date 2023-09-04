#' Data from a Univariate State Space Model (p = 1)
#'
#' @format A matrix with 100 rows (time points) and 3 columns
#'   (`eta` for the latent state,
#'   `y` for the observed data,
#'   and
#'   `time` for discrete time from 1 to 100)
#'   generated from the state space model given by
#'   \deqn{
#'     Y_{t}
#'     =
#'     \eta_{t}
#'     +
#'     \varepsilon_{t}
#'     \quad
#'     \text{with}
#'     \quad
#'     \varepsilon_{t}
#'     \sim
#'     \mathcal{N}
#'     \left( 0, 1 \right)
#'   }
#'   \deqn{
#'     \eta_{t}
#'     =
#'     0.8
#'     \eta_{t - 1}
#'     +
#'     \zeta_{t}
#'     \quad
#'     \text{with}
#'     \quad
#'     \zeta_{t}
#'     \sim
#'     \mathcal{N}
#'     \left( 0, 1 \right) .
#'   }
#' @keywords kalmanSSM data
"dat_univ_p1"
