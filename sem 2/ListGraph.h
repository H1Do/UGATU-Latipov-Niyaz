//
// Created by HidoU on 19.04.2022.
//

#ifndef LISTGRAPH_H_
#define LISTGRAPH_H_

#include "IGraph.h"

class ListGraph : IGraph {
 public:
  using AdjacenceList = std::vector<std::vector<int>>;
  explicit ListGraph(int size);
  explicit ListGraph(const IGraph* graph);
  void AddEdge(int from, int to) override;
  int VerticesCount() const override;
  void FindAllAdjacentIn(int vertex, std::vector<int>& vertices) const override;
  void FindAllAdjacentOut(int vertex, std::vector<int>& vertices) const override;

 private:
  AdjacenceList graph;
  AdjacenceList inverted_graph;
  int size;
};

#endif //LISTGRAPH_H_
