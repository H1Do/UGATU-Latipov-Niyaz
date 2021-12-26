// 63064765
// https://contest.yandex.ru/contest/32613/problems/1_2
#include <iostream>
#include <stack>

// Структура бинарного узла дерева
struct Node {
  int data;
  Node *left, *right;
  Node (int data) : data(data), left(nullptr), right(nullptr) { }
};

// Нерекурсивный прямой обход дерева с выводом в консоль
void PreOrder(Node* root) {
  std::stack<Node*>nodes;
  Node* current = root;
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
}

// Вставка ключа в дерево
void Insert(Node*& root, int value) {
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

void DeleteTree(Node* root) {
  if (root->left) DeleteTree(root->left);
  if (root->right) DeleteTree(root->right);
  delete root;
}

int main() {
  int n;
  std::cin >> n;

  int in;
  std::cin >> in;
  Node* root = new Node(in);

  for (int i = 0; i < n - 1; i++) {
    std::cin >> in;
    Insert(root, in);
  }

  PreOrder(root);
  DeleteTree(root);
  return 0;
}
