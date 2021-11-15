#include <cstdint>
#include <cstring>
#include <iostream>
// <cstring> требуется для memcpy

// Максимальный элемент в массиве
uint64_t getMax(uint64_t* arr, int n) {
  uint64_t max = arr[0];
  for (int i = 1; i < n; i++)
    if (arr[i] > max) max = arr[i];
  return max;
}

// Сортировка подсчётом выбранного разряда (байта)
void CountingSort(uint64_t* arr, int n, uint64_t byte) {
  int* count_of_numbers = new int[256]{};

  for (int i = 0; i < n; i++) 
    count_of_numbers[(arr[i] / byte) % 256]++;
  for (int i = 1; i < 256; i++) 
    count_of_numbers[i] += count_of_numbers[i - 1];

  uint64_t* temporary_array = new uint64_t[n];
  for (int i = n - 1; i >= 0; i--)
    temporary_array[--count_of_numbers[(arr[i] / byte) % 256]] = arr[i];

  delete[] count_of_numbers;
  memcpy(arr, temporary_array, n * sizeof(uint64_t));
  delete[] temporary_array;
}

// Сортировка LSD по байтам
void LSDSort(uint64_t* arr, int n) {
  uint64_t max_number = getMax(arr, n);
  for (uint64_t i = 1; i < max_number && i > 0; i *= 256)
    CountingSort(arr, n, i);
}

int main() {
  int n;
  std::cin >> n;

  uint64_t* array = new uint64_t[n];
  for (int i = 0; i < n; i++) std::cin >> array[i];

  LSDSort(array, n);

  for (int i = 0; i < n; i++) std::cout << array[i] << ' ';
  delete[] array;

  std::cout << '\n';
  return 0;
}
