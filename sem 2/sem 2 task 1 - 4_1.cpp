// https://contest.yandex.ru/contest/35212/problems/4_1
// 65685048
#include <iostream>
#include <vector>

// Функция двумерной динамики для подсчета кол-ва вариантов постройки пирамиды
uint64_t DP(int N) {
  if (N == 0) return 0;
  // Двумерный массив
  std::vector<std::vector<uint64_t>> dp(N + 1, std::vector<uint64_t>(N + 1));

  // База
  dp[0][0] = 1;

  // Проход по массиву, формула dp[n][m] = dp[n - m][1] ... dp[n - m][m - 1]
  for (int n = 1; n <= N; n++) {
    for (int m = 1; m <= n; m++) {
      for (int k = 0; k < m; k++)
          dp[n][m] += dp[n - m][k];
    }
  }

  // Поиск ответа
  uint64_t result = 0;
  for (int i = 0; i <= N; i++)
    result += dp[N][i];
  return result;
}

int main() {
  int n;
  std::cin >> n;
  std::cout << DP(n);
  return 0;
}
