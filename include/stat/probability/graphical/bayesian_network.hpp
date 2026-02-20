#pragma once

#include <unordered_set>

namespace stat::prob::graphical {

template <typename Variable>
class BayesianNetwork
{
public:
    using variable_type = Variable;

    BayesianNetwork() = default;

    void add_variable(const Variable& var);

    bool contains(const Variable& var) const noexcept;

    const std::unordered_set<Variable>& variables() const noexcept;

private:
    std::unordered_set<Variable> variables_;
};

} // namespace stat::prob::graphical

#include "bayesian_network.inl"