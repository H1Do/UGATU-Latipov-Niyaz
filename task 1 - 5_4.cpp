// 55537941
// https://contest.yandex.ru/contest/29212/problems/5_4/
#include <iostream>
#include <string>

// Функция, которая выводит приоритет введенного оператора
int Prior(char op) {
  if (op == '*' || op == '/')
    return 2;
  else if (op == '+' || op == '-')
    return 1;
  return -1;
}

template <typename T> 
class Stack {
public:
  Stack();
  ~Stack();

  void push(T a);
  T pop();

  bool empty() const { return top == -1; }
  int Size() const;
  T Top() const;

private:
  int *buffer;
  int buffer_size;
  int top;
  void BufferBoost();
};

template <typename T>
Stack<T>::Stack() : buffer_size(16), top(-1), buffer(new int[16]) {}

template <typename T> 
Stack<T>::~Stack() { delete[] buffer; }

template <typename T> 
void Stack<T>::push(T a) {
  if (top >= buffer_size - 1)
    BufferBoost();
  buffer[++top] = a;
}

template <typename T> 
T Stack<T>::pop() {
  return (top == -1) ? -1 : buffer[top--];
}

template <typename T> 
T Stack<T>::Top() const { return buffer[top]; }

template <typename T> 
int Stack<T>::Size() const { return top; }

template <typename T> 
void Stack<T>::BufferBoost() {
  int new_buffer_size = buffer_size * 2;
  int *new_buffer = new int[new_buffer_size];
  for (int i = 0; i < buffer_size; i++) {
    new_buffer[i] = buffer[i];
  }
  delete[] buffer;
  buffer = new_buffer;
  buffer_size = new_buffer_size;
}

// Функция, вычисляющая постфиксное выражение
int Calculate(const std::string &Postfix) {

  bool is_first_int = true;
  Stack<int> stack;
  int postfix_size = Postfix.size();

  for (int i = 0; i < postfix_size; i++) {

    char postfix_element = Postfix[i];

    // Считывание числа из постфиксной записи
    if (postfix_element >= '0' && postfix_element <= '9') {
      if (is_first_int) {

        is_first_int = false;
        stack.push(postfix_element - '0');

      } else {

        int temp = stack.pop();
        stack.push(temp * 10 + postfix_element - '0');
      }

    // Считывание арифметических операторов
    } else {

      if (postfix_element == ' ')
        is_first_int = true;

      else {
        int first_int = stack.pop();
        int second_int = stack.pop();

        // Операция над числами в зависимости от оператора
        if (postfix_element == '+') {
          stack.push(second_int + first_int);
        } else if (postfix_element == '-') {
          stack.push(second_int - first_int);
        } else if (postfix_element == '/') {
          stack.push(second_int / first_int);
        } else if (postfix_element == '*') {
          stack.push(second_int * first_int);
        }
      }
    }
  }

  // Возвращаем результат
  return stack.pop();
}

// Функция, преобразующая инфиксную форму записи в постфиксную
void inf_to_post(std::string &Postfix, Stack<char> &stack) {
  bool is_int = true;
  char el;

  while (std::cin >> el && el != '\n') {
    // Если встретилось число, помещаем его в результирующую строку
    if (el >= '0' && el <= '9') {
      is_int = true;
      Postfix.push_back(el);
    
    // Когда число закончилось, ставим после него пробел
    } else {
      if (is_int) {
        Postfix.push_back(' ');
        is_int = false;
      }

      // Встретив левую скобку, помещаем её в стэк
      // Встретив правую - перекидываем элементы со стэка в результирующую
      // строку, пока не стретим левую скобку
      if (el == '(' || el == ')') {
        if (el == '(') {
          stack.push(el);
        } else {
          while (stack.Top() != '(') {
            Postfix.push_back(stack.pop());
          }
          stack.pop();
        }
      
      // Встречаем оператор
      } else {

        // Если стэк пустой, помещаем оператор в него
        if (stack.empty()) {
          stack.push(el);
        // Если стэк не пустой, перемещаем элементы из него, пока не
        // встретиться оператор с меньшим приоритетом, чем считанный со строки
        } else {
          while (!stack.empty()) {
            if (Prior(stack.Top()) >= Prior(el)) {
              Postfix.push_back(stack.pop());
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
    Postfix.push_back(stack.pop());
  }
}

int main() {
  std::string Postfix;
  Stack<char> stack;

  // Считываем и преобразуем инфиксную форму запись в постфиксную
  inf_to_post(Postfix, stack);

  // Вычисляем постфиксное выражение
  std::cout << Calculate(Postfix) << std::endl;
  return 0;
}
