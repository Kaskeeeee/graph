#pragma once

#include "algorithms_base.hpp"
#include "graph_concepts.hpp"
#include "utils.hpp"
#include <unordered_map>

namespace graph::algorithms::bellman_ford {

template <concepts::Numeric WeightType> struct Node {
  WeightType distance;
  Id parent;

  Node();
};

template <concepts::Numeric WeightType>
using Tree = std::unordered_map<Id, Node<WeightType>>;

template <concepts::Graph G, concepts::Subscriptable<Id> C,
          concepts::Numeric WeightType = DecaySubscriptValue<Id, C>>
Tree<WeightType> visit(const G &graph, const Vertex &v, C &&edges_weights);

} // namespace graph::algorithms::bellman_ford

#include "algorithms/bellman_ford.i.hpp"