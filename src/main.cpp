#include "rpp.hpp"

#include <iostream>

static inline std::vector<std::vector<distance_t>> read_graph() {
    size_t vertex_n;
    std::cin >> vertex_n;

    std::vector<std::vector<distance_t>> edges(vertex_n, std::vector(vertex_n, kInfinity));

    for (auto v = 0; v < vertex_n; v++) {
        for (auto u = 0; u < vertex_n; u++) {
            std::cin >> edges[v][u];
        }
    }

    return edges;
}

static inline std::vector<std::pair<vertex_t, vertex_t>> read_subgraph_edges() {
    size_t edges_n;
    std::cin >> edges_n;

    std::vector<std::pair<vertex_t, vertex_t>> edges(edges_n);

    for (auto e = 0; e < edges_n; e++) {
        std::cin >> edges[e].first;
        std::cin >> edges[e].second;
    }

    return edges;
}

int main() {
    Graph graph(read_graph());
    auto subgraph_edges(read_subgraph_edges());
    auto ans = rpp::solve_rpp(graph, subgraph_edges);
    std::cout << "RPP solution: " << ans << std::endl;
    return 0;
}
