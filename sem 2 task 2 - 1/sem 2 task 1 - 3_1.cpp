// https://contest.yandex.ru/contest/35212/problems/3_1/
// 65395228
#include <iostream>

// Динамическое программирование для поиска min дней, до нужного кол-ва бактерий
int BeneficialBacteriaGrow(int finite_number) {
  int* dp = new int[finite_number + 1] { };

  dp[1] = 0;

  for (int i = 2; i <= finite_number; i++) {
    if (i % 5 != 0 && i % 4 != 0) {
      dp[i] = dp[i - 1] + 1;
    } else if (i % 5 == 0 && i % 4 == 0) {
      dp[i] = std::min(std::min(dp[i / 5], dp[i / 4]), dp[i - 1]) + 1;
    } else if (i % 5 == 0 && i % 4 != 0) {
      dp[i] = std::min(dp[i / 5], dp[i - 1]) + 1;
    } else if (i % 5 != 0 && i % 4 == 0) {
      dp[i] = std::min(dp[i / 4], dp[i - 1]) + 1;
    }
  }
  
  int result = dp[finite_number];
  delete[] dp;

  return result;
}

int main() {
  int n;
  std::cin >> n;

  std::cout << BeneficialBacteriaGrow(n);

  return 0;
}
