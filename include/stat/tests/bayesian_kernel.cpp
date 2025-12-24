#include <gtest/gtest.h>
#include <cmath>

// ==========================
// stat headers under test
// ==========================

#include <stat/probability/conditional/bayes.hpp>
#include <stat/probability/conditional/evidence.hpp>
#include <stat/probability/conditional/posterior_measure.hpp>
#include <stat/analysis/integration/quadrature.hpp>

// ==========================
// Test model
// ==========================

// Prior: X ~ N(0, 1)
struct GaussianPrior {
    double mean;
    double var;

    double pdf(double x) const {
        double z = x - mean;
        return std::exp(-0.5 * z * z / var)
             / std::sqrt(2.0 * M_PI * var);
    }
};

// Likelihood: Y | X ~ N(X, sigma²)
struct GaussianLikelihood {
    double var;

    double pdf(double y, double x) const {
        double z = y - x;
        return std::exp(-0.5 * z * z / var)
             / std::sqrt(2.0 * M_PI * var);
    }
};

// ==========================
// Tests
// ==========================

TEST(BayesianEvidenceTest, EvidenceIsPositiveAndFinite) {

    GaussianPrior prior{0.0, 1.0};
    GaussianLikelihood likelihood{0.25};

    stat::prob::BayesianPosterior<
        GaussianPrior,
        GaussianLikelihood,
        double,
        double
    > posterior(prior, likelihood);

    stat::analysis::integration::SimpsonQuadrature<double>
        integrator(-10.0, 10.0, 400);

    double y_obs = 1.2;

    double Z = stat::prob::evidence<
        decltype(posterior),
        decltype(integrator),
        double,
        double
    >(posterior, integrator, y_obs);

    EXPECT_TRUE(std::isfinite(Z));
    EXPECT_GT(Z, 0.0);
}

TEST(PosteriorMeasureTest, PdfIntegratesToOne) {

    GaussianPrior prior{0.0, 1.0};
    GaussianLikelihood likelihood{0.25};

    stat::prob::BayesianPosterior<
        GaussianPrior,
        GaussianLikelihood,
        double,
        double
    > posterior(prior, likelihood);

    stat::analysis::integration::SimpsonQuadrature<double>
        integrator(-10.0, 10.0, 600);

    double y_obs = 0.7;

    stat::prob::PosteriorMeasure<
        decltype(posterior),
        decltype(integrator),
        double,
        double
    > post(posterior, integrator, y_obs);

    // Numerically integrate posterior pdf
    double integral = integrator.integrate(
        [&](double x) {
            return post.pdf(x);
        }
    );

    EXPECT_NEAR(integral, 1.0, 1e-3);
}

TEST(BayesianPosteriorTest, KernelMatchesBayesRule) {

    GaussianPrior prior{0.0, 1.0};
    GaussianLikelihood likelihood{0.5};

    stat::prob::BayesianPosterior<
        GaussianPrior,
        GaussianLikelihood,
        double,
        double
    > posterior(prior, likelihood);

    double x = 0.4;
    double y = -0.2;

    double expected =
        likelihood.pdf(y, x) * prior.pdf(x);

    EXPECT_NEAR(posterior.pdf(x, y), expected, 1e-12);
}
