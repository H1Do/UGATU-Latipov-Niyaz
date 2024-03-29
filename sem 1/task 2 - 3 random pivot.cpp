// https://contest.yandex.ru/contest/30914/problems/3 Вариант с рандомным пивотом
// 58155113
#include <iostream>
#include <vector>

// Функция, выбирающая рандомный элемент и раскидывающая другие относительно
// выбранного по возрастанию, слева меньше, справа больше
int Partition(std::vector<int>& arr, int left, int right) {
  srand(time(0));
  if (left != right) std::swap(arr[left + rand() % (right - left)], arr[right]);

  int i = left - 1;

  for (int j = left; j <= right; j++)
    if (arr[j] <= arr[right]) std::swap(arr[++i], arr[j]);

  return i;
}

// Функция, определяющая порядковую статистику
int KStatLinear(std::vector<int>& arr, int n) {
  int left = 0, right = arr.size() - 1;

  while (true) {
    int pivot = Partition(arr, left, right);
    if (pivot < n)
      left = pivot + 1;
    else if (pivot > n)
      right = pivot - 1;
    else
      return arr[n];
  }
  return 0;
}

int main() {
  int n, k;
  std::cin >> n >> k;

  std::vector<int> array(n);

  for (int i = 0; i < n; i++) std::cin >> array[i];

  std::cout << KStatLinear(array, k) << '\n';
  return 0;
}
