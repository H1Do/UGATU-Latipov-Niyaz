// https://contest.yandex.ru/contest/35212/problems/5_2/
// 66222609
#include <iostream>
#include <vector>

struct TreeNode {
  int count = 0;
  int depth = 0;
  std::vector<int> children;
};

// DFS с подсчетом глубины и кол-ва дочерних вершин
void DFS1(std::vector<TreeNode>& tree, int current) {
  for (auto child : tree[current].children) {
    tree[child].depth = tree[current].depth + 1;
    DFS1(tree, child);
    tree[current].count += tree[child].count + 1;
  }
}

// DFS с подсчетом суммы растояний до всех вершин (при заданном значении result корня, от которого запускается)
void DFS2(std::vector<TreeNode>& tree, int current, std::vector<int>& result) {
  for (auto child : tree[current].children) {
    result[child] = result[current] + tree.size() - 2 * tree[child].count - 2;
    DFS2(tree, child, result);
  }
}

int main() {
  int n;
  std::cin >> n;
  std::vector<TreeNode> tree(n);

  int first, second;
  for (int i = 1; i < n; i++) {
    std::cin >> first >> second;
    tree[(first > second) ? second : first].children.push_back((first < second) ? second : first);
  }

  std::vector<int> result(n);

  DFS1(tree, 0);

  // Находим сумму расстояний до корня
  result[0] = 0;
  for (int i = 1; i < n; i++)
    result[0] += tree[i].depth;

  DFS2(tree, 0, result);

  for (int i = 0; i < n; i++)
    std::cout << result[i] << std::endl;

  return 0;
}
