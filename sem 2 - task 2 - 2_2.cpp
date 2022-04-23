// https://contest.yandex.ru/contest/36361/problems/6
// 67706606
#include <iostream>
#include <vector>
#include <set>

class Graph {
 private:
  using AdjacenceList = std::vector<std::vector<std::pair<int, unsigned long long>>>;
  AdjacenceList graph;
  int size;
 public:
  explicit Graph(int size);
  int VerticesCount() const;
  void Insert(int from, int to, int weight);
  void FindAllAdjacentOut(int vertex, std::vector<std::pair<int, unsigned long long>>& vertices) const;
};

Graph::Graph(int size) : graph(AdjacenceList(size, std::vector<std::pair<int, unsigned long long>>())),
                         size(size) { }

int Graph::VerticesCount() const {
  return size;
}

void Graph::Insert(int from, int to, int weight) {
  graph[from].push_back({to, weight});
  graph[to].push_back({from, weight});
}

void Graph::FindAllAdjacentOut(int vertex, std::vector<std::pair<int, unsigned long long>>& vertices) const {
  for (auto i : graph[vertex])
    vertices.push_back(i);
}

unsigned long long Prim(const Graph& graph) {
  std::vector<unsigned long long> distance(graph.VerticesCount(), __LONG_LONG_MAX__);
  std::vector<int> viewed(graph.VerticesCount());
  std::set<std::pair<unsigned long long, int>> order;

  unsigned long long cost_mst = 0;
  distance[0] = 0;
  order.insert({0, 0});

  std::vector<std::pair<int, unsigned long long>> vertices;
  while (!order.empty()) {
    auto [current_dist, current_vert] = *order.begin();
    order.erase(order.begin());
    cost_mst += current_dist;
    viewed[current_vert] = 1;

    vertices.clear();
    graph.FindAllAdjacentOut(current_vert, vertices);
    for (auto [vertex, weight] : vertices) {
      if (distance[vertex] > weight && viewed[vertex] == 0) {
        order.erase({distance[vertex], vertex});
        distance[vertex] = weight;
        order.insert({distance[vertex], vertex});
      }
    }
  }

  return cost_mst;
}

int main() {
  int vertices_count, edges_count;
  std::cin >> vertices_count >> edges_count;
  Graph graph(vertices_count);

  int from, to, weight;
  for (int i = 0; i < edges_count; i++) {
    std::cin >> from >> to >> weight;
    graph.Insert(--from, --to, weight);
  }

  std::cout << Prim(graph) << std::endl;
  return 0;
}
