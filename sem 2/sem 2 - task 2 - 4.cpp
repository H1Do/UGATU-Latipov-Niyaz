// https://contest.yandex.ru/contest/36361/problems/4
// 67707138
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

unsigned long long Dijkstra(int from, int to, const Graph& graph) {
  std::vector<unsigned long long> distance(graph.VerticesCount(), __LONG_LONG_MAX__);
  std::set<std::pair<unsigned long long, int>> order;

  distance[from] = 0;
  order.insert({0, from});

  std::vector<std::pair<int, unsigned long long>> vertices;
  while (!order.empty()) {
    auto [current_dist, current_vert] = *order.begin();
    order.erase(order.begin());

    vertices.clear();
    graph.FindAllAdjacentOut(current_vert, vertices);
    for (auto [vertex, weight] : vertices) {
      if (distance[vertex] > current_dist + weight) {
        order.erase({distance[vertex], vertex});
        distance[vertex] = current_dist + weight;
        order.insert({distance[vertex], vertex});
      }
    }
  }

  return distance[to];
}

int main() {
  int cities, roads;
  std::cin >> cities >> roads;
  Graph graph(cities);

  int from, to, weight;
  for (int i = 0; i < roads; i++) {
    std::cin >> from >> to >> weight;
    graph.Insert(from, to, weight);
  }
  std::cin >> from >> to;

  std::cout << Dijkstra(from, to, graph) << std::endl;
  return 0;
}
