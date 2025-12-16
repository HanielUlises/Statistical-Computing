
library(Rcpp)
library(ggplot2)
library(coda) 

beta0_true <- 2.0
beta1_true <- 0.5
sigma_true <- 1.0
n <- 100

# Generate synthetic data
set.seed(123)
X <- cbind(1, rnorm(n))
y <- beta0_true + beta1_true * X[, 2] + rnorm(n, 0, sigma_true)

# Plot the data
plot_data <- function(X, y) {
  ggplot(data.frame(X = X[, 2], y = y), aes(x = X, y = y)) +
    geom_point() +
    geom_smooth(method = "lm", se = FALSE, color = "blue") +
    ggtitle("Synthetic Data with True Regression Line")
}

# Save the synthetic data (optional)
save(X, y, file = "data/synthetic_data.RData")

# Run the MCMC sampler
set.seed(123)
results <- mcmc_sampler(y = y, X = X, iterations = 10000, 
                        beta0_init = 0.0, beta1_init = 0.0, 
                        sigma_init = 1.0, sigma_proposal = 0.1, 
                        burn_in = 1000, verbose = TRUE)

# MCMC Diagnostics
mcmc_diagnostics <- function(results) {
  mcmc_chain <- mcmc(cbind(results$beta0, results$beta1, results$sigma))
  
  # Trace plots
  traceplot(mcmc_chain, main = "Trace Plots")
  
  # Autocorrelation plots
  autocorr.plot(mcmc_chain, main = "Autocorrelation Plots")
  
  # Posterior distributions
  par(mfrow = c(3, 1))
  hist(results$beta0, breaks = 30, main = "Posterior of Beta0", xlab = "Beta0", col = "lightblue")
  hist(results$beta1, breaks = 30, main = "Posterior of Beta1", xlab = "Beta1", col = "lightblue")
  hist(results$sigma, breaks = 30, main = "Posterior of Sigma", xlab = "Sigma", col = "lightblue")
  
  # Print diagnostics
  cat("Posterior mean of beta0:", mean(results$beta0), "\n")
  cat("Posterior mean of beta1:", mean(results$beta1), "\n")
  cat("Posterior mean of sigma:", mean(results$sigma), "\n")
  cat("Acceptance rate:", results$acceptance_rate, "\n")
  
  return(mcmc_chain)
}

# Plot and save diagnostics
diagnostic_results <- mcmc_diagnostics(results)
save(diagnostic_results, file = "output/mcmc_diagnostics.RData")

ggsave("output/plots/synthetic_data_plot.png", plot = plot_data(X, y))
