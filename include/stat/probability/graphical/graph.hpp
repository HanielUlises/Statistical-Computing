#pragma once

#include "node.hpp"
#include "edge.hpp"

#include <vector>

namespace stat::prob::graphical {

class graph {
    public:
        void add_node(std::size_t id) {
            nodes_.push_back({id});
        }

        void add_edge(std::size_t parent, std::size_t child) {
            edges_.push_back({parent, child});
        }

        const std::vector<node>& nodes() const { return nodes_; }
        const std::vector<edge>& edges() const { return edges_; }

    private:
        std::vector<node> nodes_;
        std::vector<edge> edges_;
};

} // namespace stat::prob::graphical
