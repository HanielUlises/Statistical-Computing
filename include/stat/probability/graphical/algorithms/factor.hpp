#pragma once

#include <vector>
#include <unordered_map>

namespace stat::prob::graphical {


// A factor is a function over a subset of variables.
template <typename Assignment>
class factor {
    public:
        using value_type = double;

        void set(const Assignment& a, value_type v) {
            table_[a] = v;
        }

        value_type operator()(const Assignment& a) const {
            return table_.at(a);
        }

        const auto& table() const { return table_; }

    private:
        std::unordered_map<Assignment, value_type> table_;
};

} // namespace stat::prob::graphical
