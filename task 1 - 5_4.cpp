// 55488550
// https://contest.yandex.ru/contest/29212/problems/5_4/
#include <iostream>
#include <string>

int Prior(char op) {
  if (op == '*' || op == '/')
    return 2;
  else if (op == '+' || op == '-')
    return 1;
  return -1;
}

class Stack {
public:
  Stack();
  ~Stack();

  void push(int a);
  int pop();

  bool empty() const { return top == -1; }
  int Size();
  int Top();

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

int Stack::Top() { return buffer[top]; }

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

int Calculate(std::string Postfyx) {
  int first_int;
  int second_int;
  bool is_first_int = true;
  Stack stack;
  int temp = 0;

  for (int i = 0; i < (int)Postfyx.size(); i++) {
    if (Postfyx[i] >= '0' && Postfyx[i] <= '9') {
      if (is_first_int) {
        is_first_int = false;
        stack.push(Postfyx[i] - '0');
      } else {
        temp = stack.pop();
        stack.push(temp * 10 + Postfyx[i] - '0');
      }
    } else {
      if (Postfyx[i] == ' ')
        is_first_int = true;
      else {
        first_int = stack.pop();
        second_int = stack.pop();
        if (Postfyx[i] == '+') {
          stack.push(second_int + first_int);
        } else if (Postfyx[i] == '-') {
          stack.push(second_int - first_int);
        } else if (Postfyx[i] == '/') {
          stack.push(second_int / first_int);
        } else if (Postfyx[i] == '*') {
          stack.push(second_int * first_int);
        }
      }
    }
  }
  return stack.Top();
}

void inf_to_post(std::string &Postfyx, Stack &stack) {
  bool is_int = true;
  char el;

  while ((el = getchar()) && (el != '\n')) {
    if (el >= '0' && el <= '9') {
      is_int = true;
      Postfyx.push_back(el);
    } else {
      if (is_int) {
        Postfyx.push_back(' ');
        is_int = false;
      }
      if (el == '(' || el == ')') {
        if (el == '(') {
          stack.push(el);
        } else {
          while (stack.Top() != '(') {
            Postfyx.push_back(char(stack.pop()));
          }
          stack.pop();
        }
      } else {
        if (stack.empty()) {
          stack.push(el);
        } else {
          while (!stack.empty()) {
            if (Prior(char(stack.Top())) >= Prior(el)) {
              Postfyx.push_back(char(stack.pop()));
            } else {
              break;
            }
          }
          stack.push(el);
        }
      }
    }
  }
  while (!stack.empty()) {
    Postfyx.push_back(char(stack.pop()));
  }
}

int main() {
  std::string Postfix;
  Stack stack;

  inf_to_post(Postfix, stack);

  std::cout << Calculate(Postfix);
  return 0;
}
