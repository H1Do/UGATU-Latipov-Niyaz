#include <string.h>
#include <iostream>

long long getMax(long long* Arr, int n) {
  long long Max = Arr[0];
  for (int i = 1; i < n; i++)
    if (Arr[i] > Max) Max = Arr[i];
  return Max;
}

void CountingSort(long long* Arr, int n, long long byte) {
  int* CountOfNumbers = new int[256]{};
  for (int i = 0; i < n; i++) CountOfNumbers[(Arr[i] / byte) % 256]++;
  for (int i = 1; i < 256; i++) CountOfNumbers[i] += CountOfNumbers[i - 1];
  long long* TempArr = new long long[n];
  for (int i = n - 1; i >= 0; i--)
    TempArr[--CountOfNumbers[(Arr[i] / byte) % 256]] = Arr[i];
  delete[] CountOfNumbers;
  memcpy(Arr, TempArr, n * sizeof(long long));
  delete[] TempArr;
}

void LSDSort(long long* Arr, int n) {
  long long Max = getMax(Arr, n);
  for (long long i = 1; i < Max; i *= 256) {
    if (i == 0) break;
    CountingSort(Arr, n, i);
  }
}

int main() {
  int n;
  std::cin >> n;

  long long* Arr = new long long[n];
  for (int i = 0; i < n; i++) std::cin >> Arr[i];

  LSDSort(Arr, n);

  for (int i = 0; i < n; i++) std::cout << Arr[i] << ' ';
  std::cout << '\n';
  return 0;
}
