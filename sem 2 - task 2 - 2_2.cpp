// https://contest.yandex.ru/contest/36361/problems/2.2/
// 67822032
#include <iostream>
#include <vector>
#include <queue>

class Graph {
 private:
  using AdjacenceList = std::vector<std::vector<int>>;
  AdjacenceList graph;
  int size;

 public:
  explicit Graph(int size);
  void Insert(int from, int to);
  int VerticesCount() const;
  void FindAllAdjacentOut(int vertex, std::vector<int>& vertices);
};

Graph::Graph(int size) : graph(size), size(size) { }

void Graph::Insert(int from, int to) {
  graph[from].push_back(to);
  graph[to].push_back(from);
}

int Graph::VerticesCount() const {
  return size;
}

void Graph::FindAllAdjacentOut(int vertex, std::vector<int> &vertices) {
  vertices.clear();
  for (auto i : graph[vertex]) {
    vertices.push_back(i);
  }
}

int SearchCountMinDistance(int from, int to, Graph graph) {
  std::queue<int> order;
  std::vector<int> visited(graph.VerticesCount());
  std::vector<int> depth(graph.VerticesCount(), 1e9);
  std::vector<int> path(graph.VerticesCount());

  visited[from] = 1;
  depth[from] = 0;
  path[from] = 1;

  order.push(from);

  int current; std::vector<int> vertices;
  while (!order.empty()) {
    current = order.front(); order.pop();

    graph.FindAllAdjacentOut(current, vertices);
    for (auto subsequent : vertices) {
      if (!visited[subsequent]) {
        order.push(subsequent);
        visited[subsequent] = 1;
      }
      if (depth[subsequent] > depth[current] + 1) {
        depth[subsequent] = depth[current] + 1;
        path[subsequent] = path[current];
      } else if (depth[subsequent] == depth[current] + 1){
        path[subsequent] += path[current];
      }
    }
  }

  return path[to];
}

int main() {
  int vertexes_count, edges_count;
  std::cin >> vertexes_count >> edges_count;
  Graph graph(vertexes_count);

  int from, to;
  for (int i = 0; i < edges_count; i++) {
    std::cin >> from >> to;
    graph.Insert(from, to);
  }
  std::cin >> from >> to;

  std::cout << SearchCountMinDistance(from, to, graph) << std::endl;
  return 0;
}
