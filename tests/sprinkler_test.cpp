#include <iostream>
#include <vector>

#include <stat/probability/inference/exact_inference.hpp>

using namespace stat::prob::inference;
using Assignment = stat::prob::graphical::assignment<std::size_t>;
using Factor = stat::prob::graphical::Factor<Assignment>;

enum Var : std::size_t {
    C = 0,
    S = 1,
    R = 2,
    W = 3
};

int main() {

    std::vector<Factor> factors;

    // -------------------
    // P(C)
    // -------------------
    {
        Factor f({C});
        Assignment a;

        a[C] = 0; f[a] = 0.5;
        a[C] = 1; f[a] = 0.5;

        factors.push_back(f);
    }

    // -------------------
    // P(S | C)
    // -------------------
    {
        Factor f({S, C});
        Assignment a;

        a[C]=0; a[S]=0; f[a]=0.5;
        a[C]=0; a[S]=1; f[a]=0.5;

        a[C]=1; a[S]=0; f[a]=0.9;
        a[C]=1; a[S]=1; f[a]=0.1;

        factors.push_back(f);
    }

    // -------------------
    // P(R | C)
    // -------------------
    {
        Factor f({R, C});
        Assignment a;

        a[C]=0; a[R]=0; f[a]=0.8;
        a[C]=0; a[R]=1; f[a]=0.2;

        a[C]=1; a[R]=0; f[a]=0.2;
        a[C]=1; a[R]=1; f[a]=0.8;

        factors.push_back(f);
    }

    // -------------------
    // P(W | S, R)
    // -------------------
    {
        Factor f({W, S, R});
        Assignment a;

        a[S]=0; a[R]=0; a[W]=0; f[a]=1.0;
        a[S]=0; a[R]=0; a[W]=1; f[a]=0.0;

        a[S]=0; a[R]=1; a[W]=0; f[a]=0.1;
        a[S]=0; a[R]=1; a[W]=1; f[a]=0.9;

        a[S]=1; a[R]=0; a[W]=0; f[a]=0.1;
        a[S]=1; a[R]=0; a[W]=1; f[a]=0.9;

        a[S]=1; a[R]=1; a[W]=0; f[a]=0.01;
        a[S]=1; a[R]=1; a[W]=1; f[a]=0.99;

        factors.push_back(f);
    }

    ExactInference engine(factors);

    // -------------------
    // Query: P(R | W=1)
    // -------------------

    Assignment evidence;
    evidence[W] = 1;

    auto result = engine.query({R}, evidence);

    std::cout << "P(R | W=1)\n";

    for (const auto& [a, p] : result.distribution) {
        std::cout << "R=" << a.at(R) << " : " << p << "\n";
    }

    return 0;
}
