library(Rcpp)

sourceCpp("src/gibbs_sampler.cpp")

# Function to run the Gibbs sampler and return the results
run_gibbs <- function(num_samples, burn_in) {
    sampler <- GibbsSampler(num_samples, burn_in)
    samples <- sampler$sample()
    return(samples)
}

results <- run_gibbs(1000, 500)
print(results)
