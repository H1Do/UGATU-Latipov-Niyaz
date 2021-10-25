//54870888
//https://contest.yandex.ru/contest/29212/problems/5_4
#include <iostream>
#include <string>
#icnlude <cassert>

using namespace std;

int Prior(char op) {
  if (op == '*' || op == '/')
    return 2;
  else if (op == '+' || op == '-')
    return 1;
  return -1;
}

class Stack {
private:
  int buffer_size;
  int *buffer;
  int top;

public:
  explicit Stack(int _buffer_size);
  ~Stack();

  void push(int a);
  int pop();

  bool empty() const { return top == -1; }

  int size();
  int TOP();
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
  if (top != -1)
    return buffer[top--];
  else
    return -1;
}

int Stack::size() { return top; }

int Stack::TOP() { return *(buffer + top); }

int CALC(string a) {
  int Iel;
  int IIel;
  bool isFrstINT = true;
  Stack A = Stack(400);
  int temp = 0;

  for (int i = 0; i < (int)a.size(); i++) {
    if (a[i] >= '0' && a[i] <= '9') {
      if (isFrstINT) {
        isFrstINT = false;
        A.push(a[i] - '0');
      } else {
        temp = A.pop();
        A.push(temp * 10 + a[i] - '0');
      }
    } else {
      if (a[i] == ' ')
        isFrstINT = true;
      else {
        Iel = A.pop();
        IIel = A.pop();
        if (a[i] == '+') {
          A.push(IIel + Iel);
        } else if (a[i] == '-') {
          A.push(IIel - Iel);
        } else if (a[i] == '/') {
          A.push(IIel / Iel);
        } else if (a[i] == '*') {
          A.push(IIel * Iel);
        }
      }
    }
  }
  return A.TOP();
}

int main() {
  string A;
  Stack B = Stack(1000);
  bool isInt = true;
  char el;

  while (scanf("%c", &el) == 1 && el != '\n') {
    if (el >= '0' && el <= '9') {
      isInt = true;
      A.push_back(el);
    } else {
      if (isInt) {
        A.push_back(' ');
        isInt = false;
      }
      if (el == '(' || el == ')') {
        if (el == '(') {
          B.push(el);
        } else {
          while (B.TOP() != '(') {
            A.push_back(char(B.pop()));
          }
          B.pop();
        }
      } else {
        if (B.empty()) {
          B.push(el);
        } else {
          while (!B.empty()) {
            if (Prior(char(B.TOP())) >= Prior(el)) {
              A.push_back(char(B.pop()));
            } else {
              break;
            }
          }
          B.push(el);
        }
      }
    }
  }
  while (!B.empty()) {
    A.push_back(char(B.pop()));
  }
  cout << CALC(A);
  return 0;
}
