//
// Created by HidoU on 19.04.2022.
//

#ifndef MATRIXGRAPH_H_
#define MATRIXGRAPH_H_

#include "IGraph.h"

class MatrixGraph : IGraph {
 public:
  using Matrix = std::vector<std::vector<bool>>;
  explicit MatrixGraph(int size);
  explicit MatrixGraph(const IGraph* graph);
  void AddEdge(int from, int to) override;
  int VerticesCount() const override;
  void FindAllAdjacentIn(int vertex, std::vector<int>& vertices) const override;
  void FindAllAdjacentOut(int vertex, std::vector<int>& vertices) const override;

 private:
  Matrix graph;
  int size;
};

#endif //MATRIXGRAPH_H_
