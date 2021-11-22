// 58908415	
// https://contest.yandex.ru/contest/30914/problems/6
#include <ctime>
#include <iostream>
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

// Не придумал никакой оптимизации
int Pivot(unsigned int left, unsigned int right) {
  srand(time(0));
  return left + rand() % (right - left);
}

unsigned int Partition(unsigned int* arr, unsigned int left,
                       unsigned int right) {
  if (left != right) std::swap(arr[Pivot(left, right)], arr[right]);

  unsigned int i = left - 1;

  for (unsigned int j = left; j <= right; j++)
    if (arr[j] <= arr[right]) std::swap(arr[++i], arr[j]);

  return i;
}

void QuickSort(unsigned int* arr, unsigned int left, unsigned int right) {
  std::stack<unsigned int> stk;
  stk.push(left);
  stk.push(right);

  while (!stk.empty()) {
    unsigned int right = stk.top();
    stk.pop();

    unsigned int left = stk.top();
    stk.pop();

    if (right - left <= 200) {
      InsertionSort(arr + left, right - left + 1);
    } else {
      int i = Partition(arr, left, right);

      if (i > left + 1) {
        stk.push(left);
        stk.push(i - 1);
      }
      if (i < right - 1) {
        stk.push(i + 1);
        stk.push(right);
      }
    }
  }
}

void Sort(unsigned int* arr, unsigned int size) { QuickSort(arr, 0, size - 1); }
