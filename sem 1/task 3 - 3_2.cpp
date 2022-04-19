// 63045320
// https://contest.yandex.ru/contest/32613/problems/3_2
#include <iostream>
#include <stack>

// Узел авл дерева
template <typename T>
struct Node {
  T data_;
  int height_;
  int count_;
  Node *left_, *right_;

  explicit Node(const T& data) : data_(data), height_(1), count_(1), left_(nullptr), right_(nullptr) { }
};

// Класс авл дерева
template <typename T>
class AVLTree {
 private:
  Node<T>* root;

  // Функция вывода высоты дерева
  int Height(Node<T>* node) {
    return node ? node->height_ : 0;
  }

  // Функция вывода количества узлов
  int Count(Node<T>* node) {
    return node ? node->count_ : 0;
  }

  // Функция "ремонта" высот узлов дерева
  void FixNode(Node<T>* node) {
    node->height_ = std::max(Height(node->left_), Height(node->right_));
    node->count_ = Count(node->left_) + Count(node->right_) + 1;
  }

  // Правый поворот
  Node<T>* RotateRight(Node<T>* node) {
    Node<T>* temp = node->left_;
    node->left_ = temp->right_;
    temp->right_ = node;
    FixNode(node);
    FixNode(temp);
    return temp;
  }

  // Левый поворот
  Node<T>* RotateLeft(Node<T>* node) {
    Node<T>* temp = node->right_;
    node->right_ = temp->left_;
    temp->left_ = node;
    FixNode(node);
    FixNode(temp);
    return temp;
  }

  // Функция выводящая разность высот дерева - сбалансированность дерева
  int BalanceFactor(Node<T>* node) {
    return Height(node->right_) - Height(node->left_);
  }

  // Балансировка дерева
  Node<T>* Balance(Node<T>* node) {
    FixNode(node);
    if (BalanceFactor(node) == 2) {
      if (BalanceFactor(node->right_) < 0)
        node->right_ = RotateRight(node->right_);
      return RotateLeft(node);
    } else if (BalanceFactor(node) == -2) {
      if (BalanceFactor(node->left_) > 0)
        node->left_ = RotateLeft(node->left_);
      return RotateRight(node);
    }
    return node;
  }

  // Поиск узла с минимальным ключем
  Node<T>* FindMin(Node<T>* node) {
    if (node == nullptr)
      return 0;
    while (node->left_ != nullptr)
      node = node->left_;
    return node;
  }

  // Отделение узла
  Node<T>* Divide(Node<T>* node) {
    if (node->left_ == nullptr) {
      return node->right_;
    } else {
      node->left_ = Divide(node->left_);
    }
    return Balance(node);
  }

  // Вставка нового узла (вспомогательная функция)
  Node<T>* InsertFunction(Node<T>* node, const T& value) {
    if (node == nullptr)
      return new Node<T>(value);

    if (value < node->data_) {
      node->left_ = InsertFunction(node->left_, value);
    } else {
      node->right_ = InsertFunction(node->right_, value);
    }

    return Balance(node);
  }

  // Удаление узла (вспомогательная функция)
  Node<T>* DeleteFunction(Node<T>* node, const T& value) {
    if (node == nullptr)
      return node;

    if (value < node->data_) {
      node->left_ = DeleteFunction(node->left_, value);
    } else if (value > node->data_) {
      node->right_ = DeleteFunction(node->right_, value);
    } else {
      if (node->left_ == nullptr || node->right_ == nullptr) {
        Node<T>* temp = (node->left_) ? node->left_ : node->right_;
        delete node;
        return temp;
      }
      Node<T>* min = FindMin(node->right_);
      min->right_ = Divide(node->right_);
      min->left_ = node->left_;
      node = min;
    }
    return Balance(node);
  }

  // Рекурсивная функция поиска k-той порядковой статистики (вспомогательная функция)
  T KStatLinearFunction(Node<T>* node, const T& k) {
    if (Count(node->left_) == k) {
      return node->data_;
    } else if (Count(node->left_) > k) {
      return KStatLinearFunction(node->left_, k);
    } else {
      return KStatLinearFunction(node->right_, k - Count(node->left_) - 1);
    }
  }

 public:
  // Конструктор
  explicit AVLTree(const T& data) : root( new Node<T>(data) ) { }

  // Деструктор
  ~AVLTree() {
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

  AVLTree(const AVLTree& other) = delete;
  AVLTree& operator=(const AVLTree& other) = delete;
  AVLTree(AVLTree && other) = delete;
  AVLTree& operator=(AVLTree&& other) = delete;

  // Метод вставки элемента
  void Insert(const T& value) {
    root = InsertFunction(root, value);
  }

  // Метод удаления элемента
  void Delete(const T& value) {
    root = DeleteFunction(root, value);
  }

  // Метод поиска k-той порядковой статистики
  T KStatLinear(const T& k) {
    return KStatLinearFunction(root, k);
  }
};

int main() {
  int n, in, k;
  std::cin >> n >> in >> k;

  AVLTree<int> avl_tree = AVLTree<int>(in);

  std::cout << avl_tree.KStatLinear(k) << ' ';

  for (int i = 0; i < n - 1; i++) {
    std::cin >> in >> k;

    if (in >= 0) {
      avl_tree.Insert(in);
    } else {
      avl_tree.Delete(-in);
    }
    std::cout << avl_tree.KStatLinear(k) << ' ';
  }

  std::cout << std::endl;

  return 0;
}
