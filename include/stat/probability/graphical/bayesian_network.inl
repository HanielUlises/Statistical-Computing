#pragma once

#include "bayesian_network.hpp"

namespace stat::prob::graphical {

template <typename Variable>
void BayesianNetwork<Variable>::add_variable(const Variable& var)
{
    variables_.insert(var);
}

template <typename Variable>
bool BayesianNetwork<Variable>::contains(const Variable& var) const noexcept
{
    return variables_.contains(var);
}

template <typename Variable>
const std::unordered_set<Variable>&
BayesianNetwork<Variable>::variables() const noexcept
{
    return variables_;
}

} // namespace stat::prob::graphical