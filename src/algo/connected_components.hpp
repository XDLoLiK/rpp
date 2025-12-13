#pragma once

#include "../graph.hpp"

namespace algo {

using connected_component_t = std::vector<vertex_t>;

std::vector<connected_component_t> find_subgraph_connected_components(const Graph& graph,
    const std::vector<std::pair<vertex_t, vertex_t>>& subgraph_edges);

} // namespace algo
