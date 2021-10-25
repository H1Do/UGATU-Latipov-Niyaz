//54868164
//https://contest.yandex.ru/contest/29212/problems/2_3/
#include <iostream>

using std::cin;
using std::cout;

void ArrIn(int *Arr, int Size) {
  int In;
  for (int i = 0; i < Size; i++) {
    cin >> In;
    *(Arr + i) = In;
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

  int k;
  cin >> k;

  int result = 0;
  int i = 0, j = SizeB - 1;
  // По массиву B проходим от конца к началу
  // В случай совпадения, идем по А дальше.
  // Если сумма больше k, идем по B (Так как B - убывающий массив, реверснутый
  // возрастающий, мы уменьшаем сумму) Если сумма меньше k, идем по А (Так как А
  // - возрастающий массив, и мы увеличиваем сумму)
  while (i < SizeA && j >= 0) {
    int Sum = *(A + i) + *(B + j);
    if (Sum > k) {
      j--;
    } else if (Sum < k) {
      i++;
    } else if (Sum == k) {
      result++;
      i++;
    }
  }
  
  delete[] B;
  delete[] A;
  cout << result;
  return 0;
}