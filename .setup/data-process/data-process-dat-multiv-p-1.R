#' Data Analysis - `data/dat_multiv_p1.rda`
#'
DataProcessDatMultivP1 <- function() {
  rproj <- rprojroot::is_rstudio_project
  data_dir <- rproj$find_file(
    "data"
  )
  dir.create(
    path = data_dir,
    showWarnings = FALSE,
    recursive = TRUE
  )
  set.seed(42)
  time <- 100L
  k <- 2L
  alpha <- matrix(
    data = 0.0,
    nrow = k,
    ncol = 1
  )
  beta <- diag(
    x = 0.8,
    nrow = k,
    ncol = k
  )
  Psi <- diag(k)
  nu <- matrix(
    data = 0.0,
    nrow = k,
    ncol = 1
  )
  Lambda <- diag(k)
  Theta <- diag(k)
  y <- eta <- matrix(
    data = 0,
    nrow = time + 1,
    ncol = k
  )
  colnames(eta) <- paste0("eta", seq_len(k))
  colnames(y) <- paste0("y", seq_len(k))
  for (i in 2:(time + 1)) {
    eta[i, ] <- (
      alpha + beta %*% eta[(i - 1), ] + MASS::mvrnorm(
        n = 1,
        mu = rep(x = 0, times = k),
        Sigma = Psi
      )
    )
    y[i, ] <- (
      nu + Lambda %*% eta[i, ] + MASS::mvrnorm(
        n = 1,
        mu = rep(x = 0, times = k),
        Sigma = Theta
      )
    )
  }
  dat_multiv_p1 <- cbind(
    eta = eta[-1, ],
    y = y[-1, ],
    time = 1:time
  )
  save(
    dat_multiv_p1,
    file = file.path(
      data_dir,
      "dat_multiv_p1.rda"
    ),
    compress = "xz"
  )
}
DataProcessDatMultivP1()
rm(DataProcessDatMultivP1)
