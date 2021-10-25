// 54868164
// https://contest.yandex.ru/contest/29212/problems/2_3/
#include <iostream>

int necessary_sum(int *a, int *b, int size_a, int size_b, int k) {
  int result = 0;
  int i = 0, j = size_b - 1;
  while (i < size_a && j >= 0) {
    int Sum = a[i] + b[j];
    if (Sum > k) {
      j--;
    } else if (Sum < k) {
      i++;
    } else if (Sum == k) {
      result++;
      i++;
    }
  }
  return result;
}

int main() {
  int SizeA;
  std::cin >> SizeA;
  int *A = new int[SizeA];
  for (int i = 0; i < SizeA; i++) {
    std::cin >> A[i];
  }

  int SizeB;
  std::cin >> SizeB;
  int *B = new int[SizeB];
  for (int i = 0; i < SizeB; i++) {
    std::cin >> B[i];
  }

  int k;
  std::cin >> k;

  std::cout << necessary_sum(A, B, SizeA, SizeB, k);

  delete[] B;
  delete[] A;

  return 0;
}
