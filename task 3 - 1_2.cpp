// 63064765 Сейчас контест закрыт, проверить не могу, однако с тестовыми всё работает прекрасно
// https://contest.yandex.ru/contest/32613/problems/1_2
#include <iostream>
#include <stack>

template <typename T>
class BinaryTree {
 private:
  T data;
  BinaryTree *left, *right;

 public:
  // Конструктор
  explicit BinaryTree(const int &data) : data(data), left(nullptr), right(nullptr) {}

  // Нерекурсивный прямой обход дерева с выводом в консоль
  friend void PreOrder(BinaryTree<T> *root) {
    std::stack<BinaryTree<T>*> nodes;
    BinaryTree<T> *current = root;
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
  friend void Insert(BinaryTree<T> *root, const int& value) {
    BinaryTree<T> *parent = root, *current = root;

    while (current != nullptr) {
      parent = current;
      current = (value <= current->data) ? current->left : current->right;
    }

    current = new BinaryTree<T>(value);

    if (root == nullptr) {
      root = new BinaryTree<T>(value);
    } else if (value < parent->data) {
      parent->left = current;
    } else {
      parent->right = current;
    }
  }

  // Удаление всего дерева (Вопрос, если написать деструктор, можно же будет избавиться
  // от необходимости вызывать функцию, для освобождения памяти?)
  friend void DeleteTree(BinaryTree<T>* root) {
    std::stack<BinaryTree<T>*> nodes;
    nodes.push(root);

    while (!nodes.empty()) {
      BinaryTree<T>* temp = nodes.top();
      nodes.pop();

      if (temp->left) nodes.push(temp->left);
      if (temp->right) nodes.push(temp->right);
      delete temp;
    }
  }
};

int main() {
  int n;
  std::cin >> n;

  int in;
  std::cin >> in;
  auto* root = new BinaryTree<int>(in);

  for (int i = 0; i < n - 1; i++) {
    std::cin >> in;
    Insert(root, in);
  }

  PreOrder(root);
  DeleteTree(root);
  
  std::cout << std::endl;
  return 0;
}
