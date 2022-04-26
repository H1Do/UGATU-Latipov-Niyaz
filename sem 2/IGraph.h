//
// Created by HidoU on 19.04.2022.
//

#ifndef IGRAPH_H_
#define IGRAPH_H_

#include <vector>

struct IGraph {
  virtual ~IGraph() {}
  virtual void AddEdge(int from, int to) = 0;
  virtual int VerticesCount() const = 0;
  virtual void FindAllAdjacentIn(int vertex, std::vector<int>& vertices) const = 0;
  virtual void FindAllAdjacentOut(int vertex, std::vector<int>& vertices) const = 0;
};

#endif //IGRAPH_H_
