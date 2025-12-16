#include <vector>
#include <random>

class GibbsSampler {
public:
    GibbsSampler(int num_samples, int burn_in) 
        : num_samples(num_samples), burn_in(burn_in) {}

    // Simulate from conditional distributions
    std::vector<double> sample() {
        std::vector<double> samples(num_samples);
        
        // Initialize variables (theta1, theta2, ...)
        double theta1 = 0.0, theta2 = 0.0;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<> d(0, 1);
        
        for (int i = 0; i < num_samples + burn_in; ++i) {
            // Step 1: Sample theta1 | theta2
            theta1 = d(gen);
            
            // Step 2: Sample theta2 | theta1
            theta2 = d(gen);
            
            if (i >= burn_in) {
                // Store the sample after burn-in
                samples[i - burn_in] = theta1; 
            }
        }
        return samples;
    }

private:
    int num_samples;
    int burn_in;
};
