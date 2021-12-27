// 63061723
// https://contest.yandex.ru/contest/32613/problems/2_2
#include <iostream>
#include <vector>
#include <stack>

// Класс дерева, как бинарного, так и декартового
template <typename T>
class Tree {
 private:
  T data_;
  int priority_;
  Tree *left_, *right_;

 public:
  // Конструктор бинарного узла дерева
  Tree(const T& data) : data_(data), left_(nullptr), right_(nullptr) { }

  // Конструктор декартового узла дерева
  Tree(const T& data, const int& priority) : data_(data), priority_(priority), left_(nullptr),
                                  right_(nullptr) { }

  // Высота дерева
  friend int Height(Tree<T>* node) {
    if (node == nullptr)
      return 0;

    int left = Height(node->left_);
    int right = Height(node->right_);

    return ((left > right) ? left : right) + 1;
  }

  // Обход дерева в глубину с подсчётом кол-ва узлов разных высот
  friend void DFS(Tree<T>* node, int node_height, std::vector<int>& heights) {
    if (node == nullptr)
      return;
    ++heights[node_height];
    DFS(node->left_, node_height + 1, heights);
    DFS(node->right_, node_height + 1, heights);
  }

  // Ширина деревьев
  friend int Width(Tree<T>* node) {
    int height = Height(node);
    std::vector<int>heights(height);
    DFS(node, 0, heights);

    int max = 0;
    for (int i = 0; i < height; i++) {
      max = (heights[i] > max) ? heights[i] : max;
    }
    return max;
  }

  // Функция разделения для декартового дерева
  friend void Split(Tree<T>* current_node, const int& key, Tree<T>*& left, Tree<T>*& right) {
    if (current_node == nullptr) {
      left = nullptr;
      right = nullptr;
    } else if (current_node->data_ < key) {
      Split(current_node->right_, key, current_node->right_, right);
      left = current_node;
    } else {
      Split(current_node->left_, key, left, current_node->left_);
      right = current_node;
    }
  }

  // Функция слияния для декартового дерева
  friend Tree<T>* Merge(Tree<T>* left, Tree<T>* right) {
    if (left == nullptr || right == nullptr) {
      return left == nullptr ? right : left;
    }
    if (left->priority_ > right->priority_) {
      left->right_ = Merge(left->right_, right);
      return left;
    } else {
      right->left_ = Merge(left, right->left_);
      return right;
    }
  }

// Вставка ключа для декартового дерева
  friend void InsertForCartesian(Tree<T>*& root, const int& value, const int& priority) {
    Tree<T>* left;
    Tree<T>* right;

    Split(root, value, left, right);

    Tree<T>* node = new Tree(value);
    node->priority_ = priority;

    root = Merge(Merge(left, node), right);
  }

  // Вставка ключа для бинарного дерева
  friend void InsertForBinary(Tree<T>* root, const int& value) {
    if (root == nullptr) {
      root = new Tree<T>(value);
      return;
    }
    Tree<T> *parent = root, *current = root;

    while (current) {
      parent = current;
      current = (value <= current->data_) ? current->left_ : current->right_;
    }

    if (value <= parent->data_) {
      parent->left_ = new Tree<T>(value);
    } else {
      parent->right_ = new Tree<T>(value);
    }
  }

  // Удаление всего дерева
  friend void DeleteTree(Tree* root) {
    std::stack<Tree<T>*> nodes;
    nodes.push(root);

    while (!nodes.empty()) {
      Tree* temp = nodes.top();
      nodes.pop();

      if (temp->left_) nodes.push(temp->left_);
      if (temp->right_) nodes.push(temp->right_);
      delete temp;
    }
  }
};

int main() {
  int n;
  std::cin >> n;

  int key;
  int priority;
  std::cin >> key >> priority;

  auto cartesian_tree = new Tree<int>(key, priority);
  auto binary_tree = new Tree<int>(key);

  for (int i = 0; i < n - 1; i++) {
    std::cin >> key >> priority;
    InsertForCartesian(cartesian_tree, key, priority);
    InsertForBinary(binary_tree, key);
  }

  std::cout << Width(cartesian_tree) - Width(binary_tree) << std::endl;
  DeleteTree(cartesian_tree);
  DeleteTree(binary_tree);
  return 0;
}
