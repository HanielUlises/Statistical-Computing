#pragma once

#include <cstddef>

namespace stat::prob::graphical {

struct edge {
    std::size_t parent;
    std::size_t child;
};

} // namespace stat::prob::graphical
