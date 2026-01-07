#pragma once

namespace stat::prob::graphical {

template <typename Node,
          typename Parents,
          typename NonDescendants>
struct markov_property {
    static constexpr bool holds = true;
};

} // namespace stat::prob::graphical
