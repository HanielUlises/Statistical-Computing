#include <Rcpp.h>
#include <cmath>
using namespace Rcpp;

// Function to calculate the log-likelihood
double log_likelihood(NumericVector y, NumericMatrix X, double beta0, double beta1, double sigma) {
  int n = y.size();
  double ll = 0.0;
  
  for (int i = 0; i < n; i++) {
    double mu = beta0 + beta1 * X(i, 1);  // Assuming X is the design matrix with intercept
    ll += R::dnorm(y[i], mu, sigma, 1);
  }
  
  return ll;
}

// Function to calculate the log-prior
double log_prior(double beta0, double beta1, double sigma) {
  double prior_beta0 = R::dnorm(beta0, 0, 10, 1);  // N(0, 10^2) prior
  double prior_beta1 = R::dnorm(beta1, 0, 10, 1);  // N(0, 10^2) prior
  double prior_sigma = R::dgamma(1/sigma, 2, 2, 1); // Inverse-Gamma(2, 2) prior on sigma^2
  return prior_beta0 + prior_beta1 + prior_sigma;
}

// Function to calculate the log-posterior
double log_posterior(NumericVector y, NumericMatrix X, double beta0, double beta1, double sigma) {
  return log_likelihood(y, X, beta0, beta1, sigma) + log_prior(beta0, beta1, sigma);
}

// MCMC Sampler function
// [[Rcpp::export]]
List mcmc_sampler(NumericVector y, NumericMatrix X, int iterations, double beta0_init, double beta1_init, 
                  double sigma_init, double sigma_proposal, double burn_in, bool verbose) {
  int n = y.size();
  NumericVector beta0(iterations);
  NumericVector beta1(iterations);
  NumericVector sigma(iterations);
  
  beta0[0] = beta0_init;
  beta1[0] = beta1_init;
  sigma[0] = sigma_init;
  
  int accept_count = 0;

  for (int i = 1; i < iterations; i++) {
    // Propose new parameters
    double beta0_proposed = R::rnorm(beta0[i-1], sigma_proposal);
    double beta1_proposed = R::rnorm(beta1[i-1], sigma_proposal);
    double sigma_proposed = R::runif(0.1, 5.0);

    // Calculate acceptance ratio
    double log_acceptance_ratio = log_posterior(y, X, beta0_proposed, beta1_proposed, sigma_proposed) - 
                                  log_posterior(y, X, beta0[i-1], beta1[i-1], sigma[i-1]);
    
    // Accept or reject the proposal
    if (log(R::runif(0.0, 1.0)) < log_acceptance_ratio) {
      beta0[i] = beta0_proposed;
      beta1[i] = beta1_proposed;
      sigma[i] = sigma_proposed;
      accept_count++;
    } else {
      beta0[i] = beta0[i-1];
      beta1[i] = beta1[i-1];
      sigma[i] = sigma[i-1];
    }

    if (verbose && (i % (iterations / 10) == 0)) {
      Rcout << "Iteration " << i << ": beta0 = " << beta0[i] 
            << ", beta1 = " << beta1[i] << ", sigma = " << sigma[i] << std::endl;
    }
  }
  
  double acceptance_rate = (double)accept_count / iterations;
  
  return List::create(Named("beta0") = beta0[Range(burn_in, iterations-1)],
                      Named("beta1") = beta1[Range(burn_in, iterations-1)],
                      Named("sigma") = sigma[Range(burn_in, iterations-1)],
                      Named("acceptance_rate") = acceptance_rate);
}
