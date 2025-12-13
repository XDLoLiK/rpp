#include "connected_components.hpp"
#include "dfs.hpp"

namespace algo {

std::vector<connected_component_t> find_subgraph_connected_components(const Graph& graph,
    const std::vector<std::pair<vertex_t, vertex_t>>& subgraph_edges)
{
    auto sz = graph.size();
    std::vector<std::vector<vertex_t>> adj(sz);
    for (auto [u, v] : subgraph_edges) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    std::vector<bool> used(sz, false);
    std::vector<connected_component_t> components;
    auto cb = [&](vertex_t v) {
        used[v] = true;
        auto c = components.back();
        c.push_back(v);
    };
    for (auto v = 0; v < sz; ++v) {
        if (!used[v] && !adj[v].empty()) {
            components.emplace_back();
            dfs(v, adj, DfsTraversal::PreOrder, cb);
        }
    }

    return components;
}

} // namespace algo
