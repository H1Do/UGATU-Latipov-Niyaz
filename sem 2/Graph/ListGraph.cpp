//
// Created by HidoU on 19.04.2022.
//

#include "ListGraph.h"

ListGraph::ListGraph(int size) :
  graph(AdjacenceList(size, std::vector<int>())),
  inverted_graph(AdjacenceList(size, std::vector<int>())),
  size(size) { }

ListGraph::ListGraph(const IGraph* graph) :
  graph(AdjacenceList(graph->VerticesCount(), std::vector<int>())),
  inverted_graph(AdjacenceList(graph->VerticesCount(), std::vector<int>())),
  size(graph->VerticesCount()) {

  for (int i = 0; i < size; i++) {
    std::vector<int> vertices;
    graph->FindAllAdjacentOut(i, vertices);
    for (int j : vertices)
      AddEdge(i, j);
  }
}

void ListGraph::AddEdge(int from, int to) {
  graph[from].push_back(to);
  inverted_graph[to].push_back(from);
}

int ListGraph::VerticesCount() const {
  return size;
}

void ListGraph::FindAllAdjacentIn(int vertex, std::vector<int> &vertices) const {
  for (auto i : inverted_graph[vertex])
    vertices.push_back(i);
}

void ListGraph::FindAllAdjacentOut(int vertex, std::vector<int> &vertices) const {
  for (auto i : graph[vertex])
    vertices.push_back(i);
}
