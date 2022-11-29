#pragma once

#include "algorithms_base.hpp"
#include "graph_concepts.hpp"
#include <functional>
#include <unordered_map>

namespace graph::algorithms::dfs {
struct DFSVertex {
  VertexStatus status;
  int parent = -1;
  int discovery_time = -1;
  int finishing_time = -1;
};

using DFSTree = std::unordered_map<Id, DFSVertex>;

template <concepts::Graph G> DFSTree visit(const G &graph, Vertex source);

template <concepts::Graph G>
DFSTree visit(const G &graph, Vertex source, std::function<void(Vertex)> f);
} // namespace graph::algorithms::dfs

#include "algorithms/dfs.i.hpp"