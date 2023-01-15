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

#if 0

#include "algorithms/algorithms_base.hpp"
#include "base.hpp"
#include "bfs.hpp"
#include "catch.hpp"
#include "list_graph.hpp"

namespace bfs_test {
using namespace graphxx;
using namespace algorithms;

TEST_CASE("BFS Tree correct visited order", "[BFS]") {
  AdjacencyListGraph<Directedness::DIRECTED> g{};
  auto a = g.add_vertex(); // 0
  auto b = g.add_vertex(); // 1
  auto c = g.add_vertex(); // 2
  auto d = g.add_vertex(); // 3
  auto e = g.add_vertex(); // 4

  auto a_to_b = g.add_edge(a, b); // 0->1
  auto a_to_c = g.add_edge(a, c); // 0->2
  auto a_to_d = g.add_edge(a, d); // 0->3
  auto b_to_c = g.add_edge(b, c); // 1->2
  auto d_to_e = g.add_edge(d, e); // 3->4

  /*
    A--->B--->C
    --------->
    |
    |
    ---->D--->E
  */

  SECTION("check if all nodes were processed") {
    auto tree = graphxx::algorithms::bfs::visit(g, a);

    for (auto vertex : g.vertices()) {
      REQUIRE(tree[vertex].status == VertexStatus::PROCESSED);
    }
  }

  SECTION("check if all the distances from the source are correct") {
    auto tree = graphxx::algorithms::bfs::visit(g, a);

    REQUIRE(tree[a].distance == 0);
    REQUIRE(tree[b].distance == 1);
    REQUIRE(tree[c].distance == 1);
    REQUIRE(tree[d].distance == 1);
    REQUIRE(tree[e].distance == 2);
  }

  SECTION("check if all parent node are correct") {
    auto tree = graphxx::algorithms::bfs::visit(g, a);

    REQUIRE(tree[a].parent == -1);
    REQUIRE(tree[b].parent == a);
    REQUIRE(tree[c].parent == a);
    REQUIRE(tree[d].parent == a);
    REQUIRE(tree[e].parent == d);
  }

  auto a_to_a = g.add_edge(a, a); // 0->0
  auto b_to_b = g.add_edge(b, b); // 1->1
  auto c_to_b = g.add_edge(c, b); // 2->1

  /*
   <->
    A--->B--->C
    |   <->   |
    |    <-----
    --------->
    |
    |
    ---->D--->E
  */

  SECTION("check if all the distances from the source are correct, now with "
          "cycles") {
    auto tree = graphxx::algorithms::bfs::visit(g, a);

    REQUIRE(tree[a].distance == 0);
    REQUIRE(tree[b].distance == 1);
    REQUIRE(tree[c].distance == 1);
    REQUIRE(tree[d].distance == 1);
    REQUIRE(tree[e].distance == 2);
  }

  SECTION("check if all parent node are correct, now with cycles") {
    auto tree = graphxx::algorithms::bfs::visit(g, a);

    REQUIRE(tree[a].parent == -1);
    REQUIRE(tree[b].parent == a);
    REQUIRE(tree[c].parent == a);
    REQUIRE(tree[d].parent == a);
    REQUIRE(tree[e].parent == d);
  }

  SECTION("check if visit with function work properly") {
    std::vector<Vertex> vertices;

    auto tree = graphxx::algorithms::bfs::visit(
        g, a, [&](Vertex v) { vertices.push_back(v); });

    for (auto vertex : g.vertices()) {
      REQUIRE(std::find(vertices.begin(), vertices.end(), vertex) !=
              vertices.end());
    }
  }

  SECTION("work in undirected graph") {
    AdjacencyListGraph<Directedness::UNDIRECTED> g1{};
    auto a = g1.add_vertex(); // 0
    auto b = g1.add_vertex(); // 1
    auto c = g1.add_vertex(); // 2
    auto d = g1.add_vertex(); // 3
    auto e = g1.add_vertex(); // 4

    auto a_to_b = g1.add_edge(a, b); // 0->1
    auto a_to_c = g1.add_edge(a, c); // 0->2
    auto a_to_d = g1.add_edge(a, d); // 0->3
    auto b_to_c = g1.add_edge(b, c); // 1->2
    auto d_to_e = g1.add_edge(d, e); // 3->4

    auto tree = graphxx::algorithms::bfs::visit(g1, c);

    for (auto vertex : g1.vertices()) {
      REQUIRE(tree[vertex].status == VertexStatus::PROCESSED);
    }
  }
}
} // namespace bfs_test

#endif