#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>
#include <cassert>
#include <ROOT/RDataFrame.hxx>
#include <TCanvas.h>
#include <TGraph.h>
#include <TH1F.h>

class LinearRegression {
public:
    LinearRegression() : slope_(0), intercept_(0) {}

    // Fit the linear model
    template<typename... Args>
    void fit(const std::vector<double>& y, const std::vector<Args>&... x) {
        const auto& x1 = combine(x...);
        assert(x1.size() == y.size() && "Input sizes must match!");
        
        size_t n = y.size();
        double x_sum = std::accumulate(x1.begin(), x1.end(), 0.0);
        double y_sum = std::accumulate(y.begin(), y.end(), 0.0);
        double xy_sum = std::inner_product(x1.begin(), x1.end(), y.begin(), 0.0);
        double x2_sum = std::inner_product(x1.begin(), x1.end(), x1.begin(), 0.0);

        slope_ = (n * xy_sum - x_sum * y_sum) / (n * x2_sum - x_sum * x_sum);
        intercept_ = (y_sum - slope_ * x_sum) / n;
    }

    // Predict values
    template<typename... Args>
    std::vector<double> predict(const std::vector<Args>&... x) {
        const auto& x1 = combine(x...);
        std::vector<double> predictions;
        predictions.reserve(x1.size());
        for (const auto& xi : x1) {
            predictions.push_back(intercept_ + slope_ * xi);
        }
        return predictions;
    }

    double slope() const { return slope_; }
    double intercept() const { return intercept_; }

private:
    double slope_;
    double intercept_;

    template<typename... Args>
    std::vector<double> combine(const std::vector<Args>&... args) {
        static_assert(sizeof...(args) == 1, "Only single-variable regression is supported.");
        return (args + ...);
    }
};

void visualize(const std::vector<double>& x, const std::vector<double>& y, const std::vector<double>& y_pred) {
    TCanvas* c1 = new TCanvas("c1", "Linear Regression", 800, 600);
    
    TGraph* graph_data = new TGraph(x.size(), x.data(), y.data());
    graph_data->SetMarkerStyle(20);
    graph_data->SetMarkerColor(kBlue);
    graph_data->SetTitle("Data and Regression Line;X;Y");

    TGraph* graph_fit = new TGraph(x.size(), x.data(), y_pred.data());
    graph_fit->SetLineColor(kRed);
    graph_fit->SetLineWidth(2);
    graph_fit->Draw("L SAME");

    c1->Update();
    c1->SaveAs("linear_regression.png");
    delete c1;
}