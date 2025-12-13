#pragma once

#include "../graph.hpp"

namespace algo {

std::vector<std::vector<distance_t>> floyd_warshall(const Graph& graph);

} // namespace algo
