#ifndef BAYESIAN_MODEL_H
#define BAYESIAN_MODEL_H

#include <RcppArmadillo.h>

// [[Rcpp::depends(RcppArmadillo)]]
class BayesianModel {
public:
    BayesianModel(const arma::mat& X, const arma::vec& y, double sigma2, double tau2);
    arma::vec sample_posterior(int n_iter, int burn_in);

private:
    arma::mat X;       // Predictor matrix
    arma::vec y;       // Response vector
    double sigma2;     // Variance of the noise
    double tau2;       // Variance of the prior
    arma::vec beta;    // Coefficients to be estimated

    void update_beta();
    double log_posterior();
};

#endif // BAYESIAN_MODEL_H
