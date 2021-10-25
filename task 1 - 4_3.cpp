// 55394311
// https://contest.yandex.ru/contest/29212/problems/4_3
#include <cassert>
#include <iostream>

class Stack {
public:
  explicit Stack(int _buffer_size);
  ~Stack();

  void push(int a);
  int pop();

  bool empty() const { return top == -1; }
  int Size();
  void BufferBoost();

private:
  int *buffer;
  int buffer_size;
  int top;
};

Stack::Stack(int _buffer_size) : buffer_size(_buffer_size), top(-1), buffer() {
  buffer = new int[buffer_size];
}

Stack::~Stack() { delete[] buffer; }

void Stack::push(int a) {
  if (top < buffer_size - 1) {
    buffer[++top] = a;
  } else {
    BufferBoost();
    buffer[++top] = a;
  }
}

int Stack::pop() { return (top == -1) ? -1 : buffer[top--]; }

int Stack::Size() { return top; }

void Stack::BufferBoost() {
  int new_buffer_size = buffer_size * 2;
  int *new_buffer = new int[new_buffer_size];
  for (int i = 0; i < buffer_size; i++) {
    new_buffer[i] = buffer[i];
  }
  delete[] buffer;
  buffer = new_buffer;
  buffer_size = new_buffer_size;
}

class Queue {
private:
  Stack A = Stack(16);
  Stack B = Stack(16);

public:
  void push(int el) { A.push(el); }

  int pop() {
    int size = A.Size();
    if (B.empty())
      for (int i = 0; i < size + 1; i++)
        B.push(A.pop());
    return B.pop();
  }
};

bool testing(int In, int elem, Queue &A) {
  if (In == 3) {
    A.push(elem);
  } else if (In == 2) {
    if (A.pop() != elem) {
      return false;
    }
  }
  return true;
}

int main() {
  Queue A;
  bool flag = true;

  int k;
  std::cin >> k;

  for (int i = 0; i < k; i++) {
    int In;
    std::cin >> In;
    int elem;
    std::cin >> elem;

    if (!testing(In, elem, A))
      flag = false;
  }

  std::cout << ((flag) ? "YES" : "NO") << '\n';
  return 0;
}
