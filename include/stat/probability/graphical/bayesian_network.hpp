#pragma once

#include <unordered_set>
#include <unordered_map>
#include <vector>

#include "algorithms/factor.hpp"
#include "assignment.hpp"

namespace stat::prob::graphical {

template <typename Variable>
class BayesianNetwork {
    public:
        using variable_type = Variable;

        using Assignment =
            stat::prob::graphical::assignment<Variable>;

        using Factor =
            stat::prob::graphical::Factor<Assignment>;

        std::unordered_map<Variable, Factor> cpts_;

        BayesianNetwork() = default;

        void add_variable(const Variable& var);

        bool contains(const Variable& var) const noexcept;

        const std::unordered_set<Variable>& variables() const noexcept;

        void add_edge(const Variable& parent, const Variable& child);

        void set_cpt(const Variable& var, Factor cpt);
    private:
        std::unordered_set<Variable> variables_;
        std::unordered_map<Variable, std::vector<Variable>> parents_;
};

} // namespace stat::prob::graphical

#include "bayesian_network.inl"