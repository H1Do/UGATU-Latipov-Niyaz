//
// Created by HidoU on 19.04.2022.
//

#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(int size) :
    graph(Matrix(size, std::vector<int>(size))),
    size(size) { }

MatrixGraph::MatrixGraph(const IGraph* graph) :
    graph(Matrix(graph->VerticesCount(), std::vector<int>(graph->VerticesCount()))),
    size(graph->VerticesCount()) {

  for (int i = 0; i < size; i++) {
    std::vector<int> vertices;
    graph->FindAllAdjacentOut(i, vertices);
    for (int j : vertices)
      AddEdge(i, j);
  }
}

void MatrixGraph::AddEdge(int from, int to) {
  graph[from][to] = 1;
}

int MatrixGraph::VerticesCount() const {
  return size;
}

void MatrixGraph::FindAllAdjacentIn(int vertex, std::vector<int> &vertices) const {
  for (int i = 0; i < size; i++)
    if (graph[i][vertex])
      vertices.push_back(i);
}

void MatrixGraph::FindAllAdjacentOut(int vertex, std::vector<int> &vertices) const {
  for (int i = 0; i < size; i++)
    if (graph[vertex][i])
      vertices.push_back(i);
}