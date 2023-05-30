//
// Created by HidoU on 19.04.2022.
//

#include <iostream>
#include "ListGraph.h"
#include "MatrixGraph.h"
#include "ArcGraph.h"
#include "SetGraph.h"

void PrintVector(const std::vector<int>& vector) {
  for (auto elem : vector)
    std::cout << elem << ' ';
  std::cout << std::endl;
}

int main() {
  SetGraph set_graph(10);
  ListGraph list_graph(10);
  MatrixGraph matrix_graph(10);
  ArcGraph arc_graph(10);

  std::vector<std::pair<int, int>> edges;
  edges = {{0, 1}, {0, 2}, {0, 3}, {1, 2},
           {1, 5}, {1, 4}, {2, 3}, {2, 6},
           {2, 5}, {2, 7}, {2, 9}, {3, 5},
           {5, 4}, {7, 5}, {1, 8}, {9, 8}};

  for (auto edge : edges) {
    set_graph.AddEdge(edge.first, edge.second);
    list_graph.AddEdge(edge.first, edge.second);
    matrix_graph.AddEdge(edge.first, edge.second);
    arc_graph.AddEdge(edge.first, edge.second);
  }

  std::vector<int> vertexes;
  // testing FindAllAdjacentIn
  for (int i = 0; i < 10; i++) {
    std::cout << "--------------FindAllAdjacentIn - i = " << i << "-------------------" << std::endl;
    std::cout << "SetGraph: " << std::endl;
    set_graph.FindAllAdjacentOut(i, vertexes);
    PrintVector(vertexes); vertexes.clear();
    std::cout << "ListGraph: " << std::endl;
    list_graph.FindAllAdjacentOut(i, vertexes);
    PrintVector(vertexes); vertexes.clear();
    std::cout << "MatrixGraph: " << std::endl;
    matrix_graph.FindAllAdjacentOut(i, vertexes);
    PrintVector(vertexes); vertexes.clear();
    std::cout << "ArcGraph: " << std::endl;
    arc_graph.FindAllAdjacentOut(i, vertexes);
    PrintVector(vertexes); vertexes.clear();
  }

  // testing FindAllAdjacentOut
  for (int i = 0; i < 10; i++) {
    std::cout << "--------------FindAllAdjacentOut - i = " << i << "-------------------" << std::endl;
    std::cout << "SetGraph: " << std::endl;
    set_graph.FindAllAdjacentIn(i, vertexes);
    PrintVector(vertexes); vertexes.clear();
    std::cout << "ListGraph: " << std::endl;
    list_graph.FindAllAdjacentIn(i, vertexes);
    PrintVector(vertexes); vertexes.clear();
    std::cout << "MatrixGraph: " << std::endl;
    matrix_graph.FindAllAdjacentIn(i, vertexes);
    PrintVector(vertexes); vertexes.clear();
    std::cout << "ArcGraph: " << std::endl;
    arc_graph.FindAllAdjacentIn(i, vertexes);
    PrintVector(vertexes); vertexes.clear();
  }

  return 0;
}
