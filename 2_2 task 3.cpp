// 63061723
// https://contest.yandex.ru/contest/32613/problems/2_2
#include <iostream>
#include <vector>

// Структура узла дерева, как декартового, так и бинарного
struct Node {
  int data;
  int priority;
  Node *left, *right;
  // Конструктор бинарного узла дерева
  Node (int data) : data(data), left(nullptr), right(nullptr) { }
  // Конструктор декартового узла дерева
  Node (int data, int priority) : data(data), priority(priority), left(nullptr),
                                  right(nullptr) { }
  // Высота дерева
  friend int Height(Node* node) {
    if (node == nullptr)
      return 0;

    int left = Height(node->left);
    int right = Height(node->right);

    return ((left > right) ? left : right) + 1;
  }
  // Обход дерева в глубину с подсчётом кол-ва узлов разных высот
  friend void DFS(Node* node, int node_height, std::vector<int>& heights) {
    if (node == nullptr)
      return;
    ++heights[node_height];
    DFS(node->left, node_height + 1, heights);
    DFS(node->right, node_height + 1, heights);
  }
  // Ширина деревьев
  friend int Width(Node* node) {
    int height = Height(node);
    std::vector<int>heights(height);
    DFS(node, 0, heights);

    int max = 0;
    for (int i = 0; i < height; i++) {
      max = (heights[i] > max) ? heights[i] : max;
    }
    return max;
  }
};

// Функция разделения для декартового дерева
void Split(Node* current_node, int key, Node*& left, Node*& right) {
  if (current_node == nullptr) {
    left = nullptr;
    right = nullptr;
  } else if (current_node->data < key) {
    Split(current_node->right, key, current_node->right, right);
    left = current_node;
  } else {
    Split(current_node->left, key, left, current_node->left);
    right = current_node;
  }
}

// Функция слияния для декартового дерева
Node* Merge(Node* left, Node* right) {
  if (left == nullptr || right == nullptr) {
    return left == nullptr ? right : left;
  }
  if (left->priority > right->priority) {
    left->right = Merge(left->right, right);
    return left;
  } else {
    right->left = Merge(left, right->left);
    return right;
  }
}

// Вставка ключа для декартового дерева
void InsertForCartesian(Node*& root, int value, int priority) {
  Node* left;
  Node* right;

  Split(root, value, left, right);

  Node* node = new Node(value);
  node->priority = priority;

  root = Merge(Merge(left, node), right);
}

// Вставка ключа для бинарного дерева
void InsertForBinary(Node*& root, int value) {
  Node* parent = root, *current = root;

  while (current != nullptr) {
    parent = current;

    if(value < current->data) {
      current = current->left;
    } else if (value > current->data) {
      current = current->right;
    }
  }

  current = new Node(value);

  if (root == nullptr) {
    root = current;
  } else if (value < parent->data) {
    parent->left = current;
  } else {
    parent->right = current;
  }
}

// Удаление всего дерева
void DeleteTree(Node* root) {
  if (root->left) DeleteTree(root->left);
  if (root->right) DeleteTree(root->right);
  delete root;
}

int main() {
  int n;
  std::cin >> n;

  int key;
  int priority;
  std::cin >> key >> priority;

  Node* cartesian_tree = new Node(key, priority);
  Node* binary_tree = new Node(key);

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
