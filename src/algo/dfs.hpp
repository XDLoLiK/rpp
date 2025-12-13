#pragma once

#include "../graph.hpp"

#include <functional>

namespace algo {

enum DfsTraversal {
    PreOrder = 1,
    PostOrder = 2,
};

void dfs(vertex_t v, const std::vector<std::vector<vertex_t>>& adjacent, DfsTraversal order,
    std::function<void (vertex_t)> cb);

} // namespace algo
