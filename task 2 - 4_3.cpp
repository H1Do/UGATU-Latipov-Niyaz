// https://contest.yandex.ru/contest/30914/problems/4_3
// 58061829
#include <cstring>
#include <iostream>
#include <vector>
// cstring нужен для memcpy

// Слияние с подсчетом инверсий
int64_t Merge(int* arr, int left, int right, int* result_arr) {
  int64_t count_of_inversions = 0;

  int mid = (left + right) / 2;

  int i = left;
  int j = mid;
  int index = 0;

  while (i < mid && j < right) {
    if (arr[i] <= arr[j]) {
      count_of_inversions += j - mid;
      result_arr[index++] = arr[i++];
    } else {
      result_arr[index++] = arr[j++];
    }
  }
  while (i < mid) {
    count_of_inversions += right - mid;
    result_arr[index++] = arr[i++];
  }
  while (j < right) {
    result_arr[index++] = arr[j++];
  }

  return count_of_inversions;
}

// Сортировка слиянием с подсчетом инверсий
int64_t MergeSort(int* arr, int left, int right) {
  if (right - left <= 1) return 0;

  int mid = (left + right) / 2;
  int64_t count_of_inversions = 0;

  count_of_inversions += MergeSort(arr, left, mid);
  count_of_inversions += MergeSort(arr, mid, right);

  int* result_arr = new int[right - left];
  count_of_inversions += Merge(arr, left, right, result_arr);

  memcpy(arr + left, result_arr, (right - left) * sizeof(int));
  delete[] result_arr;
  return count_of_inversions;
}

int main() {
  std::vector<int> array;

  int element;
  while (std::cin >> element) array.push_back(element);

  std::cout << MergeSort(array.data(), 0, array.size()) << '\n';
  return 0;
}
