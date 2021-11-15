#include <string.h>

#include <iostream>

// Максимальный элемент в массиве
unsigned long long getMax(unsigned long long* Arr, int n) {
  unsigned long long max = Arr[0];
  for (int i = 1; i < n; i++)
    if (Arr[i] > max) max = Arr[i];
  return max;
}

// Сортировка подсчётом выбранного разряда (байта)
void CountingSort(unsigned long long* Arr, int n, unsigned long long byte) {
  int* count_of_numbers = new int[256]{};

  for (int i = 0; i < n; i++) count_of_numbers[(Arr[i] / byte) % 256]++;
  for (int i = 1; i < 256; i++) count_of_numbers[i] += count_of_numbers[i - 1];

  unsigned long long* temporary_array = new unsigned long long[n];
  for (int i = n - 1; i >= 0; i--)
    temporary_array[--count_of_numbers[(Arr[i] / byte) % 256]] = Arr[i];
  
  delete[] count_of_numbers;
  memcpy(Arr, temporary_array, n * sizeof(unsigned long long));
  delete[] temporary_array;
}

// Сортировка LSD по байтам
void LSDSort(unsigned long long* Arr, int n) {
  unsigned long long max_number = getMax(Arr, n);
  for (unsigned long long i = 1; i < max_number; i *= 256) {
    if (i == 0) {
      break;
    } else
      CountingSort(Arr, n, i);
  }
}

int main() {
  int n;
  std::cin >> n;

  unsigned long long* array = new unsigned long long[n];
  for (int i = 0; i < n; i++) std::cin >> array[i];

  LSDSort(array, n);

  for (int i = 0; i < n; i++) std::cout << array[i] << ' ';
  std::cout << '\n';
  return 0;
}
