// 55396512
// https://contest.yandex.ru/contest/29212/problems/3_4/
#include <iostream>

int BinarySearchClosest(int *arr, int elem, int size) {
  int left = 0;
  int right = size;
  int mid;
  while (right - left > 1) {
    mid = (right + left) / 2;
    if (arr[mid] > elem)
      right = mid;
    else
      left = mid;
  }
  if (left != right) {
    if (std::abs(arr[left] - elem) <= std::abs(arr[right] - elem)) {
      return left;
    }
    return right;
  }
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

  for (int i = 0; i < SizeB; i++) {
    std::cout << BinarySearchClosest(A, B[i], SizeA) << ' ';
  }

  std::cout << '\n';
  return 0;
}
