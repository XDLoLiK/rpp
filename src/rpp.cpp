#include "rpp.hpp"

#include "algo/dfs.hpp"
#include "algo/connected_components.hpp"
#include "algo/floyd_warshall.hpp"
#include "algo/hungarian.hpp"

namespace rpp {

static distance_t find_connected_components_min_cost(const Graph& graph,
    const std::vector<std::pair<vertex_t, vertex_t>>& subgraph_edges,
    const std::vector<algo::connected_component_t>& components,
    const std::vector<std::vector<distance_t>>& distances)
{
    if (components.size() <= 1) {
        // Already connected
        return 0;
    }

    auto degrees = graph.get_degrees();
    distance_t best = kInfinity;

    // chosen[i] = edge connecting component i to some previous component
    std::vector<std::pair<vertex_t, vertex_t>> chosen(components.size());

    std::function<void (size_t)> try_attach_component = [&](size_t component_idx) {
        if (component_idx == components.size()) {
            distance_t cost = 0;

            // Cost of added edges
            for (auto i = 1; i < chosen.size(); i++) {
                auto [u, v] = chosen[i];
                cost += distances[u][v];
            }

            // Parity correction
            cost += algo::hungarian(graph, distances);
            best = std::min(best, cost);
            return;
        }

        // Connect current component to any previous one
        for (auto prev = 0; prev < component_idx; prev++) {
            for (auto u : components[component_idx]) {
                for (auto v : components[prev]) {
                    chosen[component_idx] = {u, v};

                    ++degrees[u];
                    ++degrees[v];

                    try_attach_component(component_idx + 1);

                    --degrees[u];
                    --degrees[v];
                }
            }
        }
    };

    try_attach_component(1);
    return best;
}

distance_t solve_rpp(const Graph& graph,
    const std::vector<std::pair<vertex_t, vertex_t>>& subgraph_edges)
{
    auto components = algo::find_subgraph_connected_components(graph, subgraph_edges);
    auto distances = algo::floyd_warshall(graph);

    distance_t base_cost = 0;
    for (auto [u, v] : subgraph_edges) {
        base_cost += distances[u][v];
    }

    distance_t extra_cost =
        find_connected_components_min_cost(graph, subgraph_edges, components, distances);
    return base_cost + extra_cost;
}

} // namespace rpp
