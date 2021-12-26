// 63045320	
// https://contest.yandex.ru/contest/32613/problems/3_2
#include <iostream>

// Структура узла дерева
struct Node {
  int data;
  int height;
  int count;
  Node* left, *right;
  Node(int data) : data(data), height(1), count(1), left(nullptr), right(nullptr) { }
};

// Функция вывода высоты дерева
int Height(Node* node) {
  return (node) ? node->height : 0;
}

// Функция вывода количества узлов
int Count(Node* node) {
  return (node) ? node->count : 0;
}

// Функция "ремонта" высот узлов дерева
void FixNode(Node* root) {
  if (Height(root->left) > Height(root->right)) {
    root->height = Height(root->left) + 1;
  } else {
    root->height = Height(root->right) + 1;
  }
  root->count = Count(root->left) + Count(root->right) + 1;
}

// Правый поворот
Node* RotateRight(Node* node) {
  Node* temp = node->left;
  node->left = temp->right;
  temp->right = node;
  FixNode(node);
  FixNode(temp);
  return temp;
}

// Левый поворот
Node* RotateLeft(Node* node) {
  Node* temp = node->right;
  node->right = temp->left;
  temp->left = node;
  FixNode(node);
  FixNode(temp);
  return temp;
}

// Функция выводящая разность высот дерева - сбалансированность дерева
int BalanceFactor(Node* root) {
  return Height(root->right) - Height(root->left);
}

// Балансировка дерева
Node* Balance(Node* root) {
  FixNode(root);
  if (BalanceFactor(root) == 2) {
    if (BalanceFactor(root->right) < 0)
      root->right = RotateRight(root->right);
    return RotateLeft(root);
  } else if (BalanceFactor(root) == -2) {
    if (BalanceFactor(root->left) > 0)
      root->left = RotateLeft(root->left);
    return RotateRight(root);
  }
  return root;
}

// Поиск узла с минимальным ключем
Node* FindMin(Node* root) {
  if (root == nullptr)
    return 0;
  while (root->left != nullptr)
    root = root->left;
  return root;
}

// Отделение узла
Node* Divide(Node* root) {
  if (root->left == nullptr) {
    return root->right;
  } else {
    root->left = Divide(root->left);
  }
  return Balance(root);
}

// Вставка нового узла
Node* Insert(Node* root, int value) {
  if (root == nullptr)
    return new Node(value);

  if (value < root->data) {
    root->left = Insert(root->left, value);
  } else {
    root->right = Insert(root->right, value);
  }
  return Balance(root);
}

// Удаление узла
Node* Delete(Node* root, int value) {
  if (root == nullptr)
    return root;

  if (value < root->data) {
    root->left = Delete(root->left, value);
  } else if (value > root->data) {
    root->right = Delete(root->right, value);
  } else {
    if (root->left == nullptr || root->right == nullptr) {
      Node* temp = (root->left) ? root->left : root->right;
      delete root;
      return temp;
    }
    Node* min = FindMin(root->right);
    min->right = Divide(root->right);
    min->left = root->left;
    root = min;
  }
  return Balance(root);
}

// Поиск k-той порядковой статистики
int KStatLinear(Node* root, int k) {
  if (Count(root->left) == k) {
    return root->data;
  } else if (Count(root->left) > k) {
    return KStatLinear(root->left, k);
  } else {
    return KStatLinear(root->right, k - Count(root->left) - 1);
  }
}

// Удаление всего дерева
void DeleteTree(Node* root) {
  if (root->left) DeleteTree(root->left);
  if (root->right) DeleteTree(root->right);
  delete root;
}

int main() {
  int n, in, k;
  std::cin >> n >> in >> k;

  Node* avl_tree = new Node(in);
  std::cout << KStatLinear(avl_tree, k) << ' ';

  for (int i = 0; i < n - 1; i++) {
    std::cin >> in >> k;

    if (in >= 0) {
      avl_tree = Insert(avl_tree, in);
    } else {
      avl_tree = Delete(avl_tree, -in);
    }
    std::cout << KStatLinear(avl_tree, k) << ' ';
  }

  DeleteTree(avl_tree);
  std::cout << std::endl;
  return 0;
}
