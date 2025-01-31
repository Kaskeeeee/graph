/**
 * @file This file is contains an utility function to construct a path from an
 * array of nodes with parent
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

#pragma once

#include "graph_concepts.hpp" // HasParent

#include <algorithm> // std::reverse
#include <vector>    // std::vector

/// algorithms namespace contains all the algorithms available and related support structures
namespace graphxx::algorithms {

/// @brief function that construct a path from the source vertex to the target
/// one
/// @tparam Id type of vertices identifier
/// @tparam Node struct that has the "parent" property
/// @param vector_of_struct array of nodes with parent
/// @param source starting vertex
/// @param target goal vertex
/// @return vector that denote the path from source to target
template <concepts::Identifier Id, concepts::HasParent Node>
std::vector<Node> build_path(std::vector<Node> vector_of_struct, Id source,
                             Id target) {
  std::vector<Node> path;
  Node node = vector_of_struct[target];
  path.push_back(node);
  while (node.parent != source) {
    node = vector_of_struct[node.parent];
    path.push_back(node);
  }
  path.push_back(vector_of_struct[source]);
  std::reverse(path.begin(), path.end());

  return path;
}

} // namespace graphxx::algorithms