#pragma once

#include <unordered_set>
#include <unordered_map>
#include <vector>

namespace stat::prob::graphical {

template <typename Variable>
class BayesianNetwork {
    public:
        using variable_type = Variable;

        BayesianNetwork() = default;

        void add_variable(const Variable& var);

        bool contains(const Variable& var) const noexcept;

        const std::unordered_set<Variable>& variables() const noexcept;

        void add_edge(const Variable& parent, const Variable& child);
    private:
        std::unordered_set<Variable> variables_;
        std::unordered_map<Variable, std::vector<Variable>> parents_;
};

} // namespace stat::prob::graphical

#include "bayesian_network.inl"