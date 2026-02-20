#pragma once

#include <stdexcept>

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

template <typename Variable>
void BayesianNetwork<Variable>::add_edge(
    const Variable& parent,
    const Variable& child)
{
    if (!contains(parent) || !contains(child)) {
        throw std::logic_error(
            "BayesianNetwork::add_edge(): variable not registered"
        );
    }

    parents_[child].push_back(parent);
}

template <typename Variable>
void BayesianNetwork<Variable>::set_cpt(
    const Variable& var,
    Factor cpt)
{
    if (!contains(var)) {
        throw std::logic_error(
            "BayesianNetwork::set_cpt(): variable not registered"
        );
    }

    cpts_[var] = std::move(cpt);
}


} // namespace stat::prob::graphical