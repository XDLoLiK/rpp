#include "dfs.hpp"

namespace algo {

static inline void dfs_impl(vertex_t v, const std::vector<std::vector<vertex_t>>& adjacent,
    DfsTraversal order, std::function<void (vertex_t)> cb, std::vector<bool>& used)
{
    used[v] = true;
    if (order == DfsTraversal::PreOrder) {
        cb(v);
    }

    for (auto u : adjacent[v]) {
        if (!used[u]) {
            dfs_impl(u, adjacent, order, cb, used);
        }
    }

    if (order == DfsTraversal::PostOrder) {
        cb(v);
    }
}

void dfs(vertex_t v, const std::vector<std::vector<vertex_t>>& adjacent, DfsTraversal order,
    std::function<void (vertex_t)> cb)
{
    auto sz = adjacent.size();
    std::vector<bool> used(sz, false);
    dfs_impl(v, adjacent, order, cb, used);
}

} // namespace algo
