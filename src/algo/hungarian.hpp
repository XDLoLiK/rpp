#pragma once

#include "../graph.hpp"

namespace algo {

size_t hungarian(const Graph& graph);

size_t hungarian(const Graph& graph, const std::vector<std::vector<distance_t>>& dist);

} // namespace algo
