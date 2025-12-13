#include "hungarian.hpp"
#include "floyd_warshall.hpp"

namespace algo {

static inline std::vector<std::vector<distance_t>> build_cost_matrix(const Graph& graph,
    const std::vector<std::vector<distance_t>>& dist)
{
    auto sz = graph.size();
    const auto& degrees = graph.get_degrees();

    std::vector<std::vector<distance_t>> cost(sz + 1, std::vector<distance_t>(sz + 1, kInfinity));

    for (auto i = 1; i <= sz; ++i) {
        for (auto j = 1; j <= sz; ++j) {
            if (i == j) {
                cost[i][j] = kInfinity;
            } else {
                bool even_i = (degrees[i - 1] % 2 == 0);
                bool even_j = (degrees[j - 1] % 2 == 0);

                if (even_i || even_j) {
                    cost[i][j] = kInfinity;
                } else {
                    cost[i][j] = dist[i - 1][j - 1];
                }
            }
        }
    }

    return cost;
}

// Ref: https://cp-algorithms.com/graph/hungarian-algorithm.html
size_t hungarian(const Graph& graph, const std::vector<std::vector<distance_t>>& dist) {
    auto cost = build_cost_matrix(graph, dist);

    size_t n = graph.size() + 1;

    std::vector<distance_t> u(n);
    std::vector<distance_t> v(n);

    std::vector<size_t> p(n);
    std::vector<size_t> way(n);

    for (size_t i = 1; i < n; ++i) {
        p[0] = i;
        size_t j0 = 0;

        std::vector<distance_t> minv(n, kInfinity);
        std::vector<bool> used(n, false);

        do {
            used[j0] = true;
            size_t i0 = p[j0];
            distance_t delta = kInfinity;
            size_t j1 = 0;

            for (size_t j = 1; j < n; ++j) {
                if (used[j]) {
                    continue;
                }

                auto cur = cost[i0][j] - u[i0] - v[j];
                if (cur < minv[j]) {
                    minv[j] = cur;
                    way[j] = j0;
                }

                if (minv[j] < delta) {
                    delta = minv[j];
                    j1 = j;
                }
            }

            for (size_t j = 0; j < n; ++j) {
                if (used[j]) {
                    u[p[j]] += delta;
                    v[j] -= delta;
                } else {
                    minv[j] -= delta;
                }
            }

            j0 = j1;
        } while (p[j0] != 0);

        do {
            size_t j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0 != 0);
    }

    size_t answer = 0;
    for (size_t j = 1; j < n; ++j) {
        if (cost[p[j]][j] != kInfinity) {
            answer += cost[p[j]][j];
        }
    }

    // Divide by two since every edge is counted twice
    return answer / 2;
}

size_t hungarian(const Graph& graph) {
    auto dist = floyd_warshall(graph);
    return hungarian(graph, dist);
}

} // namespace algo
