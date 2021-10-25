//54870046
//https://contest.yandex.ru/contest/29212/problems/4_3
#include <assert.h>
#include <iostream>

using namespace std;

class Stack {
public:
  explicit Stack(int _buffer_size);
  ~Stack();

  void push(int a);
  int pop();

  bool empty() const { return top == -1; }
  int Size();

private:
  int *buffer;
  int buffer_size;
  int top;
};

Stack::Stack(int _buffer_size) : buffer_size(_buffer_size), top(-1) {
  buffer = new int[buffer_size];
}

Stack::~Stack() { delete[] buffer; }

void Stack::push(int a) {
  assert(top < buffer_size - 1);
  buffer[++top] = a;
}

int Stack::pop() {
  if (top != -1) {
    return buffer[top--];
  } else {
    return -1;
  }
}

int Stack::Size() { return top; }

class Queue {
private:
  Stack A = Stack(1000000);
  Stack B = Stack(1000000);

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

int main() {
  Queue A;

  int k;
  cin >> k;
  for (int i = 0; i < k; i++) {
    int In;
    int elem;
    cin >> In;
    if (In == 3) {
      cin >> elem;
      A.push(elem);
    } else if (In == 2) {
      cin >> elem;
      if (A.pop() != elem) {
        cout << "NO";
        return 0;
      }
    }
  }

  cout << "YES";
  return 0;
}
