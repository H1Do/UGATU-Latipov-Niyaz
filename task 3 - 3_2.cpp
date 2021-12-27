// 63045320
// https://contest.yandex.ru/contest/32613/problems/3_2
#include <iostream>
#include <stack>

// Класс авл дерева
template <typename T>
class AVLTree {
 private:
  T data_;
  int height_;
  int count_;
  AVLTree* left_, *right_;

 public:
  explicit AVLTree(T data) : data_(data), height_(1), count_(1), left_(nullptr), right_(nullptr) { }

  // Функция вывода высоты дерева
  friend int Height(AVLTree* node) {
    return (node) ? node->height_ : 0;
  }

  // Функция вывода количества узлов
  friend int Count(AVLTree* node) {
    return (node) ? node->count_ : 0;
  }

  // Функция "ремонта" высот узлов дерева
  friend void FixNode(AVLTree* root) {
    if (Height(root->left_) > Height(root->right_)) {
      root->height_ = Height(root->left_) + 1;
    } else {
      root->height_ = Height(root->right_) + 1;
    }
    root->count_ = Count(root->left_) + Count(root->right_) + 1;
  }

  // Правый поворот
  friend AVLTree* RotateRight(AVLTree* node) {
    AVLTree* temp = node->left_;
    node->left_ = temp->right_;
    temp->right_ = node;
    FixNode(node);
    FixNode(temp);
    return temp;
  }

  // Левый поворот
  friend AVLTree* RotateLeft(AVLTree* node) {
    AVLTree* temp = node->right_;
    node->right_ = temp->left_;
    temp->left_ = node;
    FixNode(node);
    FixNode(temp);
    return temp;
  }

  // Функция выводящая разность высот дерева - сбалансированность дерева
  friend int BalanceFactor(AVLTree* root) {
    return Height(root->right_) - Height(root->left_);
  }

  // Балансировка дерева
  friend AVLTree* Balance(AVLTree* root) {
    FixNode(root);
    if (BalanceFactor(root) == 2) {
      if (BalanceFactor(root->right_) < 0)
        root->right_ = RotateRight(root->right_);
      return RotateLeft(root);
    } else if (BalanceFactor(root) == -2) {
      if (BalanceFactor(root->left_) > 0)
        root->left_ = RotateLeft(root->left_);
      return RotateRight(root);
    }
    return root;
  }

  // Поиск узла с минимальным ключем
  friend AVLTree* FindMin(AVLTree* root) {
    if (root == nullptr)
      return 0;
    while (root->left_ != nullptr)
      root = root->left_;
    return root;
  }

  // Отделение узла
  friend AVLTree* Divide(AVLTree* root) {
    if (root->left_ == nullptr) {
      return root->right_;
    } else {
      root->left_ = Divide(root->left_);
    }
    return Balance(root);
  }

  // Вставка нового узла
  friend AVLTree* Insert(AVLTree* root, const int& value) {
    if (root == nullptr)
      return new AVLTree(value);

    if (value < root->data_) {
      root->left_ = Insert(root->left_, value);
    } else {
      root->right_ = Insert(root->right_, value);
    }
    return Balance(root);
  }

  // Удаление узла
  friend AVLTree* Delete(AVLTree* root, const int& value) {
    if (root == nullptr)
      return root;

    if (value < root->data_) {
      root->left_ = Delete(root->left_, value);
    } else if (value > root->data_) {
      root->right_ = Delete(root->right_, value);
    } else {
      if (root->left_ == nullptr || root->right_ == nullptr) {
        AVLTree* temp = (root->left_) ? root->left_ : root->right_;
        delete root;
        return temp;
      }
      AVLTree* min = FindMin(root->right_);
      min->right_ = Divide(root->right_);
      min->left_ = root->left_;
      root = min;
    }
    return Balance(root);
  }

  // Поиск k-той порядковой статистики
  friend int KStatLinear(AVLTree* root, const int& k) {
    if (Count(root->left_) == k) {
      return root->data_;
    } else if (Count(root->left_) > k) {
      return KStatLinear(root->left_, k);
    } else {
      return KStatLinear(root->right_, k - Count(root->left_) - 1);
    }
  }

  // Удаление всего дерева
  friend void DeleteTree(AVLTree* root) {
    std::stack<AVLTree<T>*> nodes;
    nodes.push(root);

    while (!nodes.empty()) {
      AVLTree* temp = nodes.top();
      nodes.pop();

      if (temp->left_) nodes.push(temp->left_);
      if (temp->right_) nodes.push(temp->right_);
      delete temp;
    }
  }
};

int main() {
  int n, in, k;
  std::cin >> n >> in >> k;

  auto* avl_tree = new AVLTree<int>(in);
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
