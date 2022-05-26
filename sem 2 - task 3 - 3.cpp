// https://contest.yandex.ru/contest/37787/problems/3/
// 68617146
#include <iostream>
#include <vector>
#include <numeric>

int64_t Manacher(const std::string& str, bool is_even) {
  std::vector<int64_t> palindromes_count(str.length());
  int bias = is_even ? 1 : 0;
  int64_t right = -1, left = -1;
  for (int64_t i = bias; i < str.size() - 1 + bias; ++i) {
    palindromes_count[i] =
        (i < right)
          ? std::min(right - i + 1, palindromes_count[left + right - i + bias])
          : 0;
    while (i + palindromes_count[i] + 1 - bias < str.size()
          && i - palindromes_count[i] - 1 >= 0
          && str[i + palindromes_count[i] + 1 - bias] == str[i - palindromes_count[i] - 1]) {
      ++palindromes_count[i];
    }
    if (i + palindromes_count[i] - 1 > right) {
      left = i - palindromes_count[i] + 1 - bias;
      right = i + palindromes_count[i] - 1;
    }
  }
  return std::accumulate(palindromes_count.begin(), palindromes_count.end(), int64_t());
}

int64_t ManacherAlgo(const std::string& str) {
  return Manacher(str, true) + Manacher(str, false);
}

int main() {
  std::string str;
  std::cin >> str;
  std::cout << ManacherAlgo(str) << std::endl;
  return 0;
}
