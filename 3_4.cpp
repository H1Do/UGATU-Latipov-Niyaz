//54868485
//https://contest.yandex.ru/contest/29212/problems/3_4/
#include <iostream>

using std::cin;
using std::cout;

void ArrIn(int *arr, int size) {
  int In;
  for (int i = 0; i < size; i++) {
    cin >> In;
    *(arr + i) = In;
  }
}
//Бинарный поиск ближайшего к заданному элементу
int BinarySearchClosest(int *arr, int elem, int size) {
  int left = 0;
  int right = size;
  int mid;
  for (int i = 0; i < 100; i++) {
    mid = (right + left) / 2;
    if (*(arr + mid) > elem)
      right = mid;
    else
      left = mid;
  }
  if (left != right) {
    if (std::abs(*(arr + left) - elem) <= std::abs(*(arr + right) - elem)) {
      return left;
    }
    return right;
  }
}

int main() {
  int SizeA;
  cin >> SizeA;
  int *A = new int[SizeA];
  ArrIn(A, SizeA);

  int SizeB;
  cin >> SizeB;
  int *B = new int[SizeB];
  ArrIn(B, SizeB);

  for (int i = 0; i < SizeB; i++) {
    cout << BinarySearchClosest(A, *(B + i), SizeA) << " ";
  }
  return 0;
}
