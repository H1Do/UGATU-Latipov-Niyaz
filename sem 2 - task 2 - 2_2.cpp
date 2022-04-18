// https://contest.yandex.ru/contest/36361/problems/2.2/
// 67160909	
#include <iostream>
#include <vector>
#include <queue>

class Graph {
 private:
  struct GraphNode {
    int depth;
    int path;
    std::vector<int> subsequents;
    GraphNode() : depth(1e9), path(0) { }
  };
  std::vector<GraphNode> graph;

 public:
  explicit Graph(int size);
  void Insert(int from, int to);
  void BFS(int from);
  int SearchCountMinDistance(int from, int to);
};

Graph::Graph(int size) : graph(std::vector<GraphNode>(size, GraphNode())) { }

void Graph::Insert(int from, int to) {
  graph[from].subsequents.push_back(to);
  graph[to].subsequents.push_back(from);
}

void Graph::BFS(int from) {
  std::queue<int> order;
  std::vector<int> visited(graph.size());
  visited[from] = 1;
  graph[from].depth = 0;
  graph[from].path = 1;
  order.push(from);

  int current;
  while (!order.empty()) {
    current = order.front(); order.pop();
    for (auto subsequent : graph[current].subsequents) {
      if (!visited[subsequent]) {
        order.push(subsequent);
        visited[subsequent] = 1;
      }
      if (graph[subsequent].depth > graph[current].depth + 1) {
        graph[subsequent].depth = graph[current].depth + 1;
        graph[subsequent].path = graph[current].path;
      } else if (graph[subsequent].depth == graph[current].depth + 1){
        graph[subsequent].path += graph[current].path;
      }
    }
  }
}

int Graph::SearchCountMinDistance(int from, int to) {
  BFS(from);
  return graph[to].path;
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

  std::cout << graph.SearchCountMinDistance(from, to) << std::endl;
  return 0;
}
