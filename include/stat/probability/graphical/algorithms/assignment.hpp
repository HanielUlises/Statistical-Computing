#pragma once

#include <unordered_map>
#include <cstddef>

namespace stat::prob::graphical {

using var_id = std::size_t;

template <typename Value>
class assignment {
    public:
        void set(var_id v, const Value& value) {
            values_[v] = value;
        }

        bool contains(var_id v) const {
            return values_.count(v) > 0;
        }

        const Value& at(var_id v) const {
            return values_.at(v);
        }

        bool compatible(const assignment& other) const {
            for (const auto& [v, val] : values_) {
                if (other.contains(v) && other.at(v) != val)
                    return false;
            }
            return true;
        }

        assignment merge(const assignment& other) const {
            assignment result = *this;
            for (const auto& [v, val] : other.values_) {
                result.values_[v] = val;
            }
            return result;
        }

        assignment remove(var_id v) const {
            assignment result = *this;
            result.values_.erase(v);
            return result;
        }

        bool operator==(const assignment& other) const {
            return values_ == other.values_;
        }

    private:
        std::unordered_map<var_id, Value> values_;
};

} // namespace stat::prob::graphical
