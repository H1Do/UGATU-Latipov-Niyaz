//
// Created by HidoU on 19.04.2022.
//

#include "SetGraph.h"

SetGraph::SetGraph(int size) :
    graph(SetList(size, std::unordered_set<int>())),
    inverted_graph(SetList(size, std::unordered_set<int>())),
    size(size) { }

SetGraph::SetGraph(const IGraph* graph) :
    graph(SetList(graph->VerticesCount(), std::unordered_set<int>())),
    inverted_graph(SetList(graph->VerticesCount(), std::unordered_set<int>())),
    size(graph->VerticesCount()) {

  for (int i = 0; i < size; i++) {
    std::vector<int> vertices;
    graph->FindAllAdjacentOut(i, vertices);
    for (int j : vertices)
      AddEdge(i, j);
  }
}

void SetGraph::AddEdge(int from, int to) {
  graph[from].insert(to);
  inverted_graph[to].insert(from);
}

int SetGraph::VerticesCount() const {
  return size;
}

void SetGraph::FindAllAdjacentIn(int vertex, std::vector<int> &vertices) const {
  for (auto i : inverted_graph[vertex])
    vertices.push_back(i);
}

void SetGraph::FindAllAdjacentOut(int vertex, std::vector<int> &vertices) const {
  for (auto i : graph[vertex])
    vertices.push_back(i);
}
