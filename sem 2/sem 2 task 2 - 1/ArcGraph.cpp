//
// Created by HidoU on 19.04.2022.
//

#include "ArcGraph.h"

ArcGraph::ArcGraph(int size) : size(size) { };

ArcGraph::ArcGraph(const IGraph *graph) : size(graph->VerticesCount()) {
  for (int i = 0; i < size; i++) {
    std::vector<int> vertices;
    graph->FindAllAdjacentOut(i, vertices);
    for (auto j : vertices)
      AddEdge(i, j);
  }
}

void ArcGraph::AddEdge(int from, int to) {
  std::pair<int, int> edge = {from, to};
  graph.push_back(edge);
}

int ArcGraph::VerticesCount() const {
  return size;
}

void ArcGraph::FindAllAdjacentOut(int vertex, std::vector<int> &vertices) const {
  for (auto i : graph)
    if (i.first == vertex)
      vertices.push_back(i.second);
}

void ArcGraph::FindAllAdjacentIn(int vertex, std::vector<int> &vertices) const {
  for (auto i : graph)
    if (i.second == vertex)
      vertices.push_back(i.first);
}