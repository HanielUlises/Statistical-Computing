#pragma once

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cstddef>

#include <stat/core/hashing/assignment_hash.hpp>

namespace stat::prob::graphical {

template <typename Assignment>
class Factor {
public:
    using value_type    = double;
    using variable_type = std::size_t;

    Factor() = default;

    explicit Factor(std::vector<variable_type> vars)
        : vars_(std::move(vars)) {}

    void set(const Assignment& a, value_type v) {
        table_[a] = v;
    }

    value_type& operator[](const Assignment& a) {
        return table_[a];
    }

    value_type operator()(const Assignment& a) const {
        return table_.at(a);
    }

    const auto& table() const { return table_; }
    const auto& variables() const { return vars_; }

    bool depends_on(variable_type v) const {
        return std::find(vars_.begin(), vars_.end(), v) != vars_.end();
    }

    Factor condition(const Assignment& evidence) const {
        Factor result(vars_);

        for (const auto& [a, p] : table_) {
            if (a.compatible(evidence))
                result.table_[a.merge(evidence)] += p;
        }

        return result;
    }

    Factor marginalize(variable_type v) const {
        std::vector<variable_type> new_vars;
        for (auto x : vars_)
            if (x != v) new_vars.push_back(x);

        Factor result(new_vars);

        for (const auto& [a, p] : table_) {
            result.table_[a.remove(v)] += p;
        }

        return result;
    }

private:
    std::vector<variable_type> vars_;

    std::unordered_map<
        Assignment,
        value_type,
        stat::core::hashing::assignment_hash<std::size_t>
    > table_;
};

} // namespace stat::prob::graphical
