#' Data Analysis - `data/dat_univ_p1.rda`
#'
DataProcessDatUnivP1 <- function() {
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
  alpha <- 0.0
  beta <- 0.8
  psi <- 1
  nu <- 0.0
  lambda <- 1
  theta <- 1
  y <- eta <- rep(
    x = 0,
    times = time + 1
  )
  for (i in 2:(time + 1)) {
    eta[i] <- alpha + beta * eta[(i - 1)] + stats::rnorm(
      n = 1,
      mean = 0,
      sd = sqrt(psi)
    )
    y[i] <- nu + lambda * eta[i] + stats::rnorm(
      n = 1,
      mean = 0,
      sd = sqrt(theta)
    )
  }
  dat_univ_p1 <- cbind(
    eta = eta[-1],
    y = y[-1],
    time = 1:time
  )
  save(
    dat_univ_p1,
    file = file.path(
      data_dir,
      "dat_univ_p1.rda"
    ),
    compress = "xz"
  )
}
DataProcessDatUnivP1()
rm(DataProcessDatUnivP1)
