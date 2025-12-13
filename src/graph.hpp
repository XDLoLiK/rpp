#pragma once

#include <vector>
#include <cinttypes>
#include <limits>

using vertex_t = size_t;
using distance_t = uint64_t;

constexpr inline distance_t kInfinity = std::numeric_limits<distance_t>::max();

class Graph {
public:
    explicit Graph(std::vector<std::vector<distance_t>> edges)
        : edges_(std::move(edges))
        , degrees_(edges.size())
    {
        auto sz = degrees_.size();
        for (auto v = 0; v < sz; v++) {
            for (auto e : edges[v]) {
                degrees_[v] += (e != 0);
            }
        }
    }

    const size_t size() const {
        return edges_.size();
    }

    const std::vector<std::vector<distance_t>>& get_edges() const {
        return edges_;
    }

    const std::vector<size_t>& get_degrees() const {
        return degrees_;
    }

private:
    std::vector<std::vector<distance_t>> edges_;
    std::vector<size_t> degrees_;
};
