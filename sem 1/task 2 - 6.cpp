// 63116316
// https://contest.yandex.ru/contest/30914/problems/6
#include "sort.h"
#include <stack>

// Сортировка вставками
void InsertionSort(unsigned int* arr, int n) {
  for (int i = 1; i < n; i++) {
    unsigned int tmp = arr[i];
    int j = i - 1;
    for (; j >= 0 && tmp < arr[j]; j--) arr[j + 1] = arr[j];
    arr[j + 1] = tmp;
  }
}

// Поиск медианы первого, последнего и среднего числа массива
size_t Pivot(unsigned int* arr, size_t left, size_t right) {
  size_t mid = (left + right) / 2;

  if (arr[left] > arr[right]) std::swap(arr[left], arr[right]);
  if (arr[left] > arr[mid]) std::swap(arr[left], arr[mid]);
  if (arr[mid] > arr[right]) std::swap(arr[mid], arr[right]);

  return mid;
}

// Разбиение Хоара
unsigned int Partition(unsigned int* arr, size_t left, size_t right) {
  if (left < right - 2) std::swap(arr[Pivot(arr, left, right)], arr[right]);

  size_t i = left;
  size_t j = right - 1;

  while (i <= j) {
    while (arr[i] < arr[right]) i++;
    while (arr[j] > arr[right]) j--;
    if (i <= j) {
      std::swap(arr[i++], arr[j--]);
    }
  }
  std::swap(arr[i], arr[right]);
  return i;
}

// Быстрая сортировка
void QuickSort(unsigned int* arr, size_t left, size_t right) {
  std::stack<std::pair<unsigned int, unsigned int>> bounds_stack;
  std::pair<unsigned int, unsigned int> bounds{left, right};
  bounds_stack.push(bounds);

  while (!bounds_stack.empty()) {
    bounds = bounds_stack.top();
    bounds_stack.pop();

    size_t left = bounds.first;
    size_t right = bounds.second;

    if (right - left <= 30) {
      InsertionSort(arr + left, right - left + 1);
    } else {
      unsigned int i = Partition(arr, left, right);

      if (i > left + 1) {
        bounds = {left, i - 1};
        bounds_stack.push(bounds);
      }
      if (i < right - 1) {
        bounds = {i + 1, right};
        bounds_stack.push(bounds);
      }
    }
  }
}

void Sort(unsigned int* arr, unsigned int size) { QuickSort(arr, 0, size - 1); }
