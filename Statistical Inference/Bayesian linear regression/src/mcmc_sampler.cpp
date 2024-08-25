#include <Rcpp.h>
#include <cmath>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace Rcpp;

// Function to calculate the log-likelihood
double log_likelihood(NumericVector y, NumericMatrix X, double beta0, double beta1, double sigma) {
  int n = y.size();
  double ll = 0.0;
  
  for (int i = 0; i < n; i++) {
    double mu = beta0 + beta1 * X(i, 1);  
    // Assuming X is the design matrix with intercept
    ll += R::dnorm(y[i], mu, sigma, 1);
  }
  
  return ll;
}

// Function to calculate the log-prior with hierarchical priors
double log_prior(double beta0, double beta1, double sigma, double tau_beta, double alpha_sigma) {
  double prior_beta0 = R::dnorm(beta0, 0, tau_beta, 1);  // N(0, tau_beta^2) prior
  double prior_beta1 = R::dnorm(beta1, 0, tau_beta, 1);  // N(0, tau_beta^2) prior
  double prior_sigma = R::dgamma(1/sigma, alpha_sigma, alpha_sigma, 1); // Inverse-Gamma(alpha_sigma, alpha_sigma) prior on sigma^2
  return prior_beta0 + prior_beta1 + prior_sigma;
}

// Function to calculate the log-posterior
double log_posterior(NumericVector y, NumericMatrix X, double beta0, double beta1, double sigma, double tau_beta, double alpha_sigma) {
  return log_likelihood(y, X, beta0, beta1, sigma) + log_prior(beta0, beta1, sigma, tau_beta, alpha_sigma);
}

// Function to save acceptance history to file
void save_acceptance_history(const std::vector<double>& acceptance_history, const std::string& filename) {
  std::ofstream file(filename.c_str());
  if (file.is_open()) {
    for (size_t i = 0; i < acceptance_history.size(); ++i) {
      file << i + 1 << "," << acceptance_history[i] << "\n";
    }
    file.close();
  } else {
    Rcpp::Rcout << "Error: Unable to open file " << filename << "\n";
  }
}

// Adaptive Metropolis-Hastings MCMC Sampler function
// [[Rcpp::export]]
List mcmc_sampler(NumericVector y, NumericMatrix X, int iterations, double beta0_init, double beta1_init, 
                  double sigma_init, double tau_beta, double alpha_sigma, double sigma_proposal, 
                  double burn_in, bool verbose, double adapt_rate, int adapt_interval, const std::string& output_filename) {
  
  int n = y.size();
  NumericVector beta0(iterations);
  NumericVector beta1(iterations);
  NumericVector sigma(iterations);
  std::vector<double> acceptance_history(iterations, 0.0);
  
  beta0[0] = beta0_init;
  beta1[0] = beta1_init;
  sigma[0] = sigma_init;
  
  int accept_count = 0;

  for (int i = 1; i < iterations; i++) {
    // Adaptive proposal step size
    if (i % adapt_interval == 0 && i <= burn_in) {
      sigma_proposal = sigma_proposal * exp(adapt_rate * (accept_count / (double)i - 0.234));
    }

    // Propose new parameters
    double beta0_proposed = R::rnorm(beta0[i-1], sigma_proposal);
    double beta1_proposed = R::rnorm(beta1[i-1], sigma_proposal);
    double sigma_proposed = R::runif(0.1, 5.0);

    // Calculate acceptance ratio
    double log_acceptance_ratio = log_posterior(y, X, beta0_proposed, beta1_proposed, sigma_proposed, tau_beta, alpha_sigma) - 
                                  log_posterior(y, X, beta0[i-1], beta1[i-1], sigma[i-1], tau_beta, alpha_sigma);
    
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

    // Store acceptance rate history
    acceptance_history[i] = (double)accept_count / i;

    // Verbose output for debugging and tracking progress
    if (verbose && (i % (iterations / 10) == 0)) {
      Rcout << "Iteration " << i << ": beta0 = " << beta0[i] 
            << ", beta1 = " << beta1[i] << ", sigma = " << sigma[i] << std::endl;
      Rcout << "Current proposal standard deviation: " << sigma_proposal << std::endl;
      Rcout << "Current acceptance rate: " << acceptance_history[i] << std::endl;
    }
  }
  
  // Final acceptance rate
  double final_acceptance_rate = (double)accept_count / iterations;
  
  // Save acceptance history to file
  save_acceptance_history(acceptance_history, output_filename);

  return List::create(Named("beta0") = beta0[Range(burn_in, iterations-1)],
                      Named("beta1") = beta1[Range(burn_in, iterations-1)],
                      Named("sigma") = sigma[Range(burn_in, iterations-1)],
                      Named("acceptance_rate") = final_acceptance_rate,
                      Named("acceptance_history") = acceptance_history);
}

// Function to calculate Gelman-Rubin diagnostic
// [[Rcpp::export]]
double gelman_rubin_diagnostic(NumericMatrix chains) {
  int n = chains.nrow();
  int m = chains.ncol();
  NumericVector chain_means(m);
  double overall_mean = 0.0;
  
  for (int j = 0; j < m; ++j) {
    chain_means[j] = mean(chains(_, j));
    overall_mean += chain_means[j];
  }
  overall_mean /= m;
  
  double B = 0.0;  // Between-chain variance
  for (int j = 0; j < m; ++j) {
    B += pow(chain_means[j] - overall_mean, 2);
  }
  B *= (double)n / (m - 1);
  
  double W = 0.0;  // Within-chain variance
  for (int j = 0; j < m; ++j) {
    NumericVector chain = chains(_, j);
    W += var(chain);
  }
  W /= m;
  
  double var_plus = (double)(n - 1) / n * W + B / n;
  double R_hat = sqrt(var_plus / W);
  
  return R_hat;
}