library(Rcpp)
library(ggplot2)
library(RcppArmadillo)

sourceCpp("../src/bayesian_model.cpp")

# Step 1: Data Loading and Preprocessing
data <- read.csv("path_to_your_data/data.csv")
X <- as.matrix(data[, -ncol(data)])
y <- as.vector(data[, ncol(data)])

# Step 2: Hyperparameters
sigma2 <- 1.0  # Noise variance
tau2 <- 1.0    # Prior variance
n_iter <- 10000
burn_in <- 2000

# Step 3: Run MCMC Sampling
posterior_samples <- run_mcmc(X, y, sigma2, tau2, n_iter, burn_in)

# Step 4: Post-Processing and Visualization
posterior_mean <- mean(posterior_samples)
posterior_sd <- sd(posterior_samples)

# Plot posterior distribution
ggplot(data.frame(Samples = posterior_samples), aes(x = Samples)) +
    geom_histogram(bins = 30, fill = "blue", alpha = 0.7) +
    geom_vline(aes(xintercept = posterior_mean), color = "red", linetype = "dashed", size = 1) +
    labs(title = "Posterior Distribution of the Bayesian Model",
         x = "Log Posterior", y = "Frequency")

# Step 5: Output Results
cat("Posterior Mean:", posterior_mean, "\n")
cat("Posterior SD:", posterior_sd, "\n")
