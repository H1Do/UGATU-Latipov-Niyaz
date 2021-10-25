// 55377775
// https://contest.yandex.ru/contest/29212/problems/3_4/
#include <iostream>

// For я использую для того, чтобы в случай отсутсвия нужного элемента (когда мы
// ищем ближайший по значению) Цикл While не уходил в бесконечный цикл. В For
// число 17, так как (110000 / 2 ^ 17) < 1. 110000 - макс. размер массива А по условию.
int BinarySearchClosest(int *arr, int elem, int size) {
  int left = 0;
  int right = size;
  int mid;
  for (int i = 0; i < 17; i++) {
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
