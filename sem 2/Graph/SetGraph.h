//
// Created by HidoU on 19.04.2022.
//

#ifndef SETGRAPH_H_
#define SETGRAPH_H_

#include "IGraph.h"
#include <unordered_set>

class SetGraph : IGraph {
 public:
  using SetList = std::vector<std::unordered_set<int>>;
  explicit SetGraph(int size);
  explicit SetGraph(const IGraph* graph);
  void AddEdge(int from, int to) override;
  int VerticesCount() const override;
  void FindAllAdjacentIn(int vertex, std::vector<int>& vertices) const override;
  void FindAllAdjacentOut(int vertex, std::vector<int>& vertices) const override;

 private:
  SetList graph;
  SetList inverted_graph;
  int size;
};

#endif //SETGRAPH_H_
