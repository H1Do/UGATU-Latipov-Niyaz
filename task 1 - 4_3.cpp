// 55485600
// https://contest.yandex.ru/contest/29212/problems/4_3
#include <cassert>
#include <iostream>

class Stack {
public:
  Stack();
  ~Stack();

  void push(int a);
  int pop();

  bool empty() const { return top == -1; }
  int Size();

private:
  int *buffer;
  int buffer_size;
  int top;
  void BufferBoost();
};

Stack::Stack() : buffer_size(16), top(-1), buffer(new int[16]) {}

Stack::~Stack() { delete[] buffer; }

void Stack::push(int a) {
  if (top >= buffer_size - 1)
    BufferBoost();
  buffer[++top] = a;
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
  Stack StackA;
  Stack StackB;

public:
  void push(int el) { StackA.push(el); }

  int pop() {
    int size = StackA.Size();
    if (StackB.empty())
      for (int i = 0; i < size + 1; i++)
        StackB.push(StackA.pop());
    return StackB.pop();
  }
};

bool testing(std::pair<int, int> Elem, Queue &Q) {
  if (Elem.first == 3)
    Q.push(Elem.second);
  else if (Elem.first == 2 && Q.pop() != Elem.second)
    return false;
  return true;
}

int main() {
  Queue queue;
  bool flag = true;

  int k;
  std::cin >> k;
  std::pair<int, int> Elem;

  for (int i = 0; i < k; i++) {
    std::cin >> Elem.first >> Elem.second;

    if (!testing(Elem, queue)) {
      flag = false;
      break;
    }
  }

  std::cout << (flag ? "YES" : "NO") << '\n';
  return 0;
}
