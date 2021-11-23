// 59015475 TL, а в моих тестах ошибка, причем по отдельности сортировки работают
// исправно. Если есть такая возможность, можете помочь
// https://contest.yandex.ru/contest/30914/problems/6
#include <stack>

#include "sort.h"

void InsertionSort(unsigned int* arr, int n) {
  for (int i = 1; i < n; i++) {
    unsigned int tmp = arr[i];
    int j = i - 1;
    for (; j >= 0 && tmp < arr[j]; j--) arr[j + 1] = arr[j];
    arr[j + 1] = tmp;
  }
}

// Поиск медианы первого, последнего и среднего числа массива
int Pivot(unsigned int* arr, size_t left, size_t right) {
  return (arr[left] + arr[right] + arr[(left + right) / 2]) / 3;
}

// Разбиение Хоара
unsigned int Partition(unsigned int* arr, size_t left, size_t right) {
  if (left == right) return left;
  unsigned int pivot = Pivot(arr, left, right);

  size_t i = left;
  size_t j = right - 1;

  while (i <= j) {
    while (arr[i] < pivot) i++;
    while (arr[j] > pivot) j--;
    if (i <= j) {
      std::swap(arr[i], arr[j]);
      i++;
      j--;
    }
  }
  return i;
}

void QuickSort(unsigned int* arr, size_t left, size_t right) {
  std::stack<std::pair<unsigned int, unsigned int>> stk;
  std::pair<unsigned int, unsigned int> pr{left, right};
  stk.push(pr);

  while (!stk.empty()) {
    pr = stk.top();
    stk.pop();

    size_t left = pr.first;
    size_t right = pr.second;

    if (right - left <= 30) {
      InsertionSort(arr + left, right - left + 1);
    } else {
      int i = Partition(arr, left, right);

      if (i > left + 1) {
        pr.first = left;
        pr.second = i - 1;
        stk.push(pr);
      }
      if (i < right - 1) {
        pr.first = i + 1;
        pr.second = right;
        stk.push(pr);
      }
    }
  }
}

void Sort(unsigned int* arr, unsigned int size) { QuickSort(arr, 0, size - 1); }
