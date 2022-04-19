// 63064765
// https://contest.yandex.ru/contest/32613/problems/1_2
#include <iostream>
#include <stack>

// Узел бинарного дерева
template <typename T>
struct Node {
  T data;
  Node *left, *right;
  explicit Node(const T& data) : data(data), left(nullptr), right(nullptr) {}
};

// Бинарное дерево
template <typename T>
class BinaryTree {
 private:
  Node<T>* root;

 public:
  // Конструктор
  explicit BinaryTree(const T& data) : root(new Node<T>(data)) {}

  // Деструктор
  ~BinaryTree() {
    std::stack<Node<T>*> nodes;
    nodes.push(root);

    while (!nodes.empty()) {
      Node<T>* temp = nodes.top();
      nodes.pop();

      if (temp->left) nodes.push(temp->left);
      if (temp->right) nodes.push(temp->right);
      delete temp;
    }
  }

  BinaryTree(const BinaryTree& other) = delete;
  BinaryTree& operator=(const BinaryTree& other) = delete;
  BinaryTree(BinaryTree && other) = delete;
  BinaryTree& operator=(BinaryTree&& other) = delete;

  // Нерекурсивный прямой обход дерева с выводом в консоль
  void PreOrder() {
    std::stack<Node<T>*> nodes;
    Node<T> *current = root;
    nodes.push(current);

    while (!nodes.empty()) {
      current = nodes.top();
      nodes.pop();

      std::cout << current->data << ' ';

      if (current->right != nullptr)
        nodes.push(current->right);
      if (current->left != nullptr)
        nodes.push(current->left);
    }
  };

  // Вставка ключа в дерево
  void Insert(const T& value) {
    if (root == nullptr) {
      root = new Node<T>(value);
      return;
    }
    Node<T> *parent = root, *current = root;

    while (current) {
      parent = current;
      current = (value <= current->data) ? current->left : current->right;
    }

    (value <= parent->data) ? parent->left : parent->right = new Node<T>(value);
  }
};

int main() {
  int n;
  std::cin >> n;

  int in;
  std::cin >> in;
  BinaryTree<int> tree = BinaryTree<int>(in);

  for (int i = 0; i < n - 1; i++) {
    std::cin >> in;
    tree.Insert(in);
  }

  tree.PreOrder();

  std::cout << std::endl;
  return 0;
}
