/**
 * @file This file is the header implementation of Dijkstra algorithm
 *
 * @copyright Copyright © 2023 Matteo Cavaliere, Cristiano Di Bari, Michele
 * Quaresmini, Andrea Cinelli. All rights reserved.
 *
 * @license{<blockquote>
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * </blockquote>}
 *
 * @author Matteo Cavaliere, Cristiano Di Bari, Michele Quaresmini, Andrea
 * Cinelli
 * @date December, 2022
 * @version v1.0
 */

#include "algorithms/dijkstra.hpp" // dijkstra
#include "base.hpp"                // Vertex
#include "exceptions.hpp"          // exceptions::InvariantViolationException
#include "graph_concepts.hpp"      // Graph
#include "numeric_utils.hpp"       // sum_will_overflow

#include <limits> // std::numeric_limits
#include <queue>  // std::priority_queue
#include <vector> // std::vector

namespace graphxx::algorithms {

template <concepts::Graph G, std::invocable<Edge<G>> Weight, typename Distance>
std::vector<DijkstraNode<Vertex<G>, Distance>>
dijkstra(const G &graph, Vertex<G> source, Weight weight) {

  using NodeType = DijkstraNode<Vertex<G>, Distance>;
  constexpr auto distance_upperbound = std::numeric_limits<Distance>::max();
  std::vector<NodeType> distance_tree{
      graph.num_vertices(),
      NodeType{.distance = distance_upperbound, .parent = INVALID_VERTEX<G>}};

  using WeightedVertex = std::tuple<Distance, Vertex<G>>;
  std::priority_queue<WeightedVertex, std::vector<WeightedVertex>,
                      std::greater<WeightedVertex>>
      queue;

  distance_tree[source].distance = 0;
  queue.push({distance_tree[source].distance, source});

  while (!queue.empty()) {
    auto u = std::get<1>(queue.top());
    queue.pop();

    for (auto&& edge : graph[u]) {
      auto v = graph.get_target(edge);
      Distance edge_weight = weight(edge);

      if (edge_weight < 0) {
        throw exceptions::InvariantViolationException(
            "negative edge weight found");
      }

      if (utils::sum_will_overflow(distance_tree[u].distance, edge_weight)) {
        continue;
      }

      Distance alternative_distance = distance_tree[u].distance + edge_weight;
      if (alternative_distance < distance_tree[v].distance) {
        distance_tree[v].distance = alternative_distance;
        distance_tree[v].parent = u;
        queue.push({alternative_distance, v});
      }
    }
  }

  return distance_tree;
}

} // namespace graphxx::algorithms