// https://contest.yandex.ru/contest/36361/problems/4
// 67515239
#include <iostream>
#include <vector>
#include <set>

class Graph {
 private:
  std::vector<std::vector<std::pair<int, unsigned long long>>> graph;

 public:
  explicit Graph(int size);
  void Insert(int from, int to, int weight);
  unsigned long long Dijkstra(int from, int to);
};

Graph::Graph(int size) : graph(std::vector<std::vector<std::pair<int, unsigned long long>>>(size, std::vector<std::pair<int, unsigned long long>>())) { }

void Graph::Insert(int from, int to, int weight) {
  graph[from].push_back({to, weight});
  graph[to].push_back({from, weight});
}

unsigned long long Graph::Dijkstra(int from, int to) {
  std::vector<unsigned long long> distance (graph.size(), __LONG_LONG_MAX__);

  distance[from] = 0;
  std::set<std::pair<int, unsigned long long>> order;
  order.insert({0, from});

  while (!order.empty()) {
    auto [current_dist, current_vert] = *order.begin();
    order.erase(order.begin());

    for (auto [vertex, weight] : graph[current_vert]) {
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
  std::cout << graph.Dijkstra(from, to) << std::endl;
  return 0;
}
