// 63061723
// https://contest.yandex.ru/contest/32613/problems/2_2
#include <iostream>
#include <vector>
#include <stack>

// Гибридный узел дерева, как для бинарного, так и для декартового
template <typename T>
struct Node {
  T data_;
  int priority_;
  Node *left_, *right_;
  // Конструктор декартового узла
  explicit Node(const T& data, const int& priority) : data_(data), priority_(priority),
                                                      left_(nullptr), right_(nullptr) {}
  // Конструктор бинарного узла
  explicit Node(const T& data) : data_(data), left_(nullptr), right_(nullptr) {}
};

// Декартовое дерево
template <typename T>
class CartesianTree {
 private:
  Node<T>* root;

 public:

  // Конструктор
  CartesianTree(const T& data, const int& priority) : root(new Node(data, priority)) { }

  // Деструктор
  ~CartesianTree() {
    std::stack<Node<T>*> nodes;
    nodes.push(root);

    while (!nodes.empty()) {
      Node<T>* temp = nodes.top();
      nodes.pop();

      if (temp->left_) nodes.push(temp->left_);
      if (temp->right_) nodes.push(temp->right_);
      delete temp;
    }
  }

  CartesianTree(const CartesianTree& other) = delete;
  CartesianTree& operator=(const CartesianTree& other) = delete;
  CartesianTree(CartesianTree && other) = delete;
  CartesianTree& operator=(CartesianTree&& other) = delete;

  // Высота дерева, ф-ия рекурсивная, как метод сделать не могу
  int Height(Node<T>* node) {
    if (node == nullptr)
      return 0;

    int left = Height(node->left_);
    int right = Height(node->right_);

    return std::max(left, right) + 1;
  }

  // Обход в ширину с подсчётом кол-ва узлов на разных уровнях, тоже рекурсивная
  void DFS(Node<T>* node, int node_height, std::vector<int>& heights) {
    if (node == nullptr)
      return;
    ++heights[node_height];
    DFS(node->left_, node_height + 1, heights);
    DFS(node->right_, node_height + 1, heights);
  }

  // Ширина дерева
  int Width() {
    int height = Height(root);
    std::vector<int> heights(height);
    DFS(root, 0, heights);

    int max = 0;
    for (int i = 0; i < height; i++)
      if (heights[i] > max) max = heights[i];

    return max;
  }

  void Split(Node<T>* node, const T& key, Node<T>*& left, Node<T>*& right) {
    if (node == nullptr) {
      left = nullptr;
      right = nullptr;
    } else if (node->data_ < key) {
      Split(node->right_, key, node->right_, right);
      left = node;
    } else {
      Split(node->left_, key, left, node->left_);
      right = node;
    }
  }

  Node<T>* Merge(Node<T>* left, Node<T>* right) {
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

  // Вставка
  void Insert(const T& value, const int& priority) {
    Node<T>* left;
    Node<T>* right;

    Split(root, value, left, right);

    Node<T>* node = new Node(value);
    node->priority_ = priority;

    root = Merge(Merge(left, node), right);
  }
};

// Бинарное дерево
template <typename T>
class BinaryTree {
 private:
  Node<T> *root;

 public:
  // Конструктор
  BinaryTree(const T &data) : root(new Node(data)) {}

  // Деструктор
  ~BinaryTree() {
    std::stack<Node<T> *> nodes;
    nodes.push(root);

    while (!nodes.empty()) {
      Node<T> *temp = nodes.top();
      nodes.pop();

      if (temp->left_) nodes.push(temp->left_);
      if (temp->right_) nodes.push(temp->right_);
      delete temp;
    }
  }

  BinaryTree(const BinaryTree& other) = delete;
  BinaryTree& operator=(const BinaryTree& other) = delete;
  BinaryTree(BinaryTree && other) = delete;
  BinaryTree& operator=(BinaryTree&& other) = delete;

  // Высота дерева, ф-ия рекурсивная, как метод сделать не могу
  int Height(Node<T>* node) {
    if (node == nullptr)
      return 0;

    int left = Height(node->left_);
    int right = Height(node->right_);

    return std::max(left, right) + 1;
  }

  // Обход в ширину с подсчётом кол-ва узлов на разных уровнях, тоже рекурсивная
  void DFS(Node<T>* node, int node_height, std::vector<int>& heights) {
    if (node == nullptr)
      return;
    ++heights[node_height];
    DFS(node->left_, node_height + 1, heights);
    DFS(node->right_, node_height + 1, heights);
  }

  // Ширина дерева
  int Width() {
    int height = Height(root);
    std::vector<int> heights(height);
    DFS(root, 0, heights);

    int max = 0;
    for (int i = 0; i < height; i++)
      if (heights[i] > max) max = heights[i];

    return max;
  }

  // Вставка ключа для бинарного дерева
  void Insert(const T& value) {
    if (root == nullptr) {
      root = new Node<T>(value);
      return;
    }
    Node<T> *parent = root, *current = root;

    while (current) {
      parent = current;
      current = (value <= current->data_) ? current->left_ : current->right_;
    }

    if (value <= parent->data_) {
      parent->left_ = new Node<T>(value);
    } else {
      parent->right_ = new Node<T>(value);
    }
  }
};

int main() {
  int n;
  std::cin >> n;

  int key;
  int priority;
  std::cin >> key >> priority;

  auto cartesian_tree = CartesianTree<int>(key, priority);
  auto binary_tree = BinaryTree<int>(key);

  for (int i = 0; i < n - 1; i++) {
    std::cin >> key >> priority;
    cartesian_tree.Insert(key, priority);
    binary_tree.Insert(key);
  }

  std::cout << cartesian_tree.Width() - binary_tree.Width() << std::endl;
  return 0;
}
