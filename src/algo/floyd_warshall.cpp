#include "floyd_warshall.hpp"

#include <algorithm>

namespace algo {

std::vector<std::vector<distance_t>> floyd_warshall(const Graph& graph) {
    auto sz = graph.size();
    auto dist(graph.get_edges());

    for (auto k = 0; k < sz; k++) {
        for (auto i = 0; i < sz; i++) {
            for (auto j = 0; j < sz; j++) {
                dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    return dist;
}

} // namespace algo
