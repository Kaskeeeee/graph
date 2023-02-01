/**
 * @file
 *
 * @copyright Copyright © 2022 Graphxx. All rights reserved.
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

#include "base.hpp"
#include "exceptions.hpp"
#include "list_graph.hpp"
#include "utils/tuple_utils.hpp"

#include <algorithm>
#include <type_traits>

namespace graphxx {

template <concepts::Identifier Id, Directedness D, typename... AttributesType>
AdjacencyListGraph<Id, D, AttributesType...>::AdjacencyListGraph(){};

template <concepts::Identifier Id, Directedness D, typename... AttributesType>
AdjacencyListGraph<Id, D, AttributesType...>::AdjacencyListGraph(
    const AdjacencyListGraph &graph) {
  for (auto &&vertex : graph) {
    for (auto &&edge : vertex) {
      std::apply(
          [&](auto &&...attributes) {
            add_edge(source(edge), target(edge), attributes...);
          },
          get_elements_from_index<2>(edge));
    }
  }
};

template <concepts::Identifier Id, Directedness D, typename... AttributesType>
void AdjacencyListGraph<Id, D, AttributesType...>::add_vertex() {
  _adj.emplace_back();
};

template <concepts::Identifier Id, Directedness D, typename... AttributesType>
void AdjacencyListGraph<Id, D, AttributesType...>::add_vertex(Vertex vertex) {
  for (auto i = _adj.size(); i <= vertex; ++i) {
    _adj.emplace_back();
  }
};

template <concepts::Identifier Id, Directedness D, typename... AttributesType>
void AdjacencyListGraph<Id, D, AttributesType...>::add_edge(Vertex source, Vertex target, Attributes &attrs) {
  add_vertex(source);
  add_vertex(target);

  std::apply(
      [&](auto &&...props) {
        _adj[source].emplace_back(source, target, props...);
      },
      attrs);

  if (DIRECTEDNESS == Directedness::UNDIRECTED) {
    std::apply(
        [&](auto &&...props) {
          _adj[target].emplace_back(target, source, props...);
        },
        attrs);
  }
};

template <concepts::Identifier Id, Directedness D, typename... AttributesType>
void AdjacencyListGraph<Id, D, AttributesType...>::remove_vertex(Vertex vertex) {
  if (!has_vertex(vertex))
    return;

  _adj[vertex].clear();
  
  for (size_t i = 0; i < Base::size(); i++) {
    _adj[i].remove_if([&](auto&& edge) { return target(edge) == vertex; })
  }
};

template <concepts::Identifier Id, Directedness D, typename... AttributesType>
void AdjacencyListGraph<Id, D, AttributesType...>::remove_edge(Vertex source, Vertex target) {
  if (!has_edge(source, target))
    return;

  _adj[source].remove_if([&](auto&& edge) { return target(edge) == target; })
  
  if (DIRECTEDNESS == Directedness::UNDIRECTED) {
    _adj[target].remove_if([&](auto&& edge) { return target(edge) == source; })
  }
};

template <concepts::Identifier Id, Directedness D, typename... AttributesType>
void AdjacencyListGraph<Id, D, AttributesType...>::set_attributes(
    Vertex source, Vertex target, Attributes &attrs) {
      if (!has_edge(target, source))
        return;

      auto it = std::ranges::find(_adj[source], [&](auto &&edge) { return target(edge) == target; });

      if (*it == _adj[source].end())
        return

      set_elements_from_index<2>(*it, attrs);
}

template <concepts::Identifier Id, Directedness D, typename... AttributesType>
size_t AdjacencyListGraph<Id, D, AttributesType...>::num_attributes() const {
  return sizeof...(AttributesType);
}

template <concepts::Identifier Id, Directedness D, typename... AttributesType>
Id AdjacencyListGraph<Id, D, AttributesType...>::source(Edge& edge) const {
  return std::get<0>(edge);
}

template <concepts::Identifier Id, Directedness D, typename... AttributesType>
Id AdjacencyListGraph<Id, D, AttributesType...>::target(Edge& edge) const {
  return std::get<1>(edge);
}

template <concepts::Identifier Id, Directedness D, typename... AttributesType>
size_t AdjacencyListGraph<Id, D, AttributesType...>::num_vertices() const {
  return _adj.size();
}

template <concepts::Identifier Id, Directedness D, typename... AttributesType>
size_t AdjacencyListGraph<Id, D, AttributesType...>::num_edges() const {
  size_t count = 0;
  for (size_t i = 0; i < _adj.size(); i++) {
    count += _adj[i].size();
  }
  return count;
}

template <concepts::Identifier Id, Directedness D, typename... AttributesType>
const AdjacencyListGraph<Id, D, AttributesType...>::Edge& AdjacencyListGraph<Id, D, AttributesType...>::get_edge(Vertex source, Vertex target) const {
    auto it = std::ranges::find(_adj[source], [&](auto &&edge) { return target(edge) == target; });

    if (*it == _adj[source].end())
      return
}

} // namespace graphxx