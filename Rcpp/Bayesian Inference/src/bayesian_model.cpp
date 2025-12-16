#include "bayesian_model.h"
#include <RcppArmadillo.h>

BayesianModel::BayesianModel(const arma::mat& X, const arma::vec& y, double sigma2, double tau2)
    : X(X), y(y), sigma2(sigma2), tau2(tau2), beta(arma::zeros(X.n_cols)) {}

// Function to update beta in each MCMC iteration
void BayesianModel::update_beta() {
    arma::mat XtX = X.t() * X;
    arma::vec Xty = X.t() * y;
    arma::mat Sigma = arma::inv(XtX / sigma2 + arma::eye(X.n_cols, X.n_cols) / tau2);
    arma::vec mu = Sigma * Xty / sigma2;
    beta = mu + arma::chol(Sigma, "lower") * arma::randn<arma::vec>(X.n_cols);
}

// Log posterior function
double BayesianModel::log_posterior() {
    double log_prior = -0.5 * arma::dot(beta, beta) / tau2;
    double log_likelihood = -0.5 * arma::dot(y - X * beta, y - X * beta) / sigma2;
    return log_prior + log_likelihood;
}

// MCMC sampling function
arma::vec BayesianModel::sample_posterior(int n_iter, int burn_in) {
    arma::vec posteriors(n_iter - burn_in);
    for (int i = 0; i < n_iter; ++i) {
        update_beta();
        if (i >= burn_in) {
            posteriors(i - burn_in) = log_posterior();
        }
    }
    return posteriors;
}

// [[Rcpp::export]]
arma::vec run_mcmc(const arma::mat& X, const arma::vec& y, double sigma2, double tau2, int n_iter, int burn_in) {
    BayesianModel model(X, y, sigma2, tau2);
    return model.sample_posterior(n_iter, burn_in);
}
