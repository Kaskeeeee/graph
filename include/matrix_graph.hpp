#pragma once
#include "base.hpp"
#include "id_manager.hpp"
#include "graph_concepts.hpp"

#include <unordered_map>

namespace graph {

template <concepts::Orientable GraphType> class AdjacencyMatrixGraph {
protected:
  using AdjacencyMap = std::unordered_map<Id, Id>;
  using AdjacencyMatrix = std::unordered_map<Id, AdjacencyMap>;
  using EdgeMap = std::unordered_map<Id, Edge>;

public:
  using Tag = GraphType;
  
  AdjacencyMatrixGraph();

  Vertex add_vertex();
  void remove_vertex(const Vertex &);

  Edge add_edge(const Vertex &, const Vertex &);
  void remove_edge(const Edge &);

  auto vertices() const;
  auto edges() const;
  auto out_edges(const Vertex &) const;
  auto in_edges(const Vertex &) const;
  
  Vertex get_vertex(const Id &id) const;
  Edge get_edge(const Id &id) const;

private:
  AdjacencyMatrix _adj;
  EdgeMap _edge_map;

  utils::IdManager _vertex_id_manager;
  utils::IdManager _edge_id_manager;
};
} // namespace graph

#include "matrix_graph.i.hpp"