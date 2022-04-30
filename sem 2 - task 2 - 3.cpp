#include <iostream>
#include <vector>
#include <cstring>

class Graph {
 public:
  using ArcList = std::vector<std::pair<int, int>>;
  explicit Graph(int size);
  void Insert(int from, int to, double converse);
  [[nodiscard]] int VerticesCount() const;
  [[nodiscard]] double GetWeight(int from, int to) const;
  void FindAllAdjacentOut(int vertex, std::vector<int>& vertices) const;

 private:
  ArcList graph;
  std::vector<std::vector<double>> weights;
  int size;
};

Graph::Graph(int size) : size(size), weights(size, std::vector<double>(size)) { };

void Graph::Insert(int from, int to, double converse) {
  graph.push_back({from, to});
  weights[from][to] = converse;
}

int Graph::VerticesCount() const {
  return size;
}

double Graph::GetWeight(int from, int to) const {
  return weights[from][to];
}

void Graph::FindAllAdjacentOut(int vertex, std::vector<int> &vertices) const {
  vertices.clear();
  for (auto i : graph)
    if (i.first == vertex)
      vertices.push_back(i.second);
}

// Обратная от релаксации функция
bool AntiRelax(int from, int to, const Graph& graph, std::vector<double>& dp) {
  if (dp[to] < dp[from] * graph.GetWeight(from, to) && dp[from] != -1e9) {
    dp[to] = dp[from] * graph.GetWeight(from, to);
    return true;
  }
  return false;
}

// Алгоритм Беллмана-Форда, но с поиском положительных циклов
bool IsArbitrage(const Graph& graph) {
  std::vector<double> dp(graph.VerticesCount());
  std::vector<int> vertices;

  for (int start = 0; start < graph.VerticesCount(); start++) {
    memset(&dp[0], -1e9, graph.VerticesCount() * sizeof(double));
    dp[start] = 1;

    for (int step = 0; step < graph.VerticesCount() - 1; step++) {
      for (int from = 0; from < graph.VerticesCount(); from++) {
        graph.FindAllAdjacentOut(from, vertices);
        for (auto to : vertices)
          AntiRelax(from, to, graph, dp);
      }
    }

    for (int from = 0; from < graph.VerticesCount(); from++) {
      graph.FindAllAdjacentOut(from, vertices);
      for (auto to : vertices)
        if (AntiRelax(from, to, graph, dp))
          return true;
    }
  }
  return false;
}

int main() {
  int n;
  std::cin >> n;
  Graph graph(n);

  double conversion;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i != j) {
        std::cin >> conversion;
        if (conversion != -1)
          graph.Insert(i, j, conversion);
      }
    }
  }

  std::cout << (IsArbitrage(graph) ? "YES" : "NO") << std::endl;
  return 0;
}
