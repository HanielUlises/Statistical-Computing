#pragma once

#include <vector>
#include <unordered_map>
#include <stdexcept>

namespace stat::prob::graphical {

// Discrete conditional probability table
//   P(X | Parents)
template <typename X, typename Parents>
class conditional_probability_table {
public:
    using value_type = double;

    // Key = (x, parents)
    using key_type = std::pair<X, Parents>;

    void set(const X& x,
             const Parents& parents,
             value_type p)
    {
        table_[{x, parents}] = p;
    }

    // Lookup P(x | parents)
    value_type pdf(const X& x,
                   const Parents& parents) const
    {
        auto it = table_.find({x, parents});
        if (it == table_.end()) {
            throw std::runtime_error("CPT entry not found");
        }
        return it->second;
    }

private:
    struct key_hash {
        std::size_t operator()(const key_type& k) const {
            return std::hash<X>{}(k.first) ^
                   (std::hash<Parents>{}(k.second) << 1);
        }
    };

    std::unordered_map<key_type, value_type, key_hash> table_;
};

} // namespace stat::prob::graphical
