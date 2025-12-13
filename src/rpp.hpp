#pragma once

#include "graph.hpp"

namespace rpp {

distance_t solve_rpp(const Graph& graph,
    const std::vector<std::pair<vertex_t, vertex_t>>& subgraph_edges);

} // namespace rpp
