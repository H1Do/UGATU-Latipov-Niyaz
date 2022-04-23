//
// Created by HidoU on 19.04.2022.
//

#ifndef ARCGRAPH_H_
#define ARCGRAPH_H_

#include "IGraph.h"

class ArcGraph : IGraph {
 public:
  using ArcList = std::vector<std::pair<int, int>>;
  explicit ArcGraph(int size);
  explicit ArcGraph(const IGraph* graph);
  void AddEdge(int from, int to) override;
  int VerticesCount() const override;
  void FindAllAdjacentIn(int vertex, std::vector<int>& vertices) const;
  void FindAllAdjacentOut(int vertex, std::vector<int>& vertices) const;

 private:
  ArcList graph;
  int size;
};

#endif //ARCGRAPH_H_
