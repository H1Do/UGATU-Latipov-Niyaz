// https://contest.yandex.ru/contest/37787/problems/3/ 
// 68525665
#include <iostream>
#include <vector>

void ManacherOdd(const std::string& str, std::vector<int64_t>& palindromes_count) {
  int64_t right = -1, left = -1;
  for (int64_t i = 0; i < str.size() - 1; ++i) {
    if (i < right) {
      palindromes_count[i] = std::min(right - i + 1, palindromes_count[left + right - i]);
    } else {
      palindromes_count[i] = 0;
    }
    while (i + palindromes_count[i] + 1 < str.size() && i - palindromes_count[i] - 1 >= 0 && str[i + palindromes_count[i] + 1] == str[i - palindromes_count[i] - 1]) {
      ++palindromes_count[i];
    }
    if (i + palindromes_count[i] - 1 > right) {
      left = i - palindromes_count[i] + 1;
      right = i + palindromes_count[i] - 1;
    }
  }
}

void ManacherEven(const std::string& str, std::vector<int64_t>& palindromes_count) {
  int64_t right = -1, left = -1;
  for (int64_t i = 1; i < str.size(); ++i) {
    if (i < right) {
      palindromes_count[i] = std::min(right - i + 1, palindromes_count[left + right - i + 1]);
    } else {
      palindromes_count[i] = 0;
    }
    while (i + palindromes_count[i] < str.size() && i - palindromes_count[i] - 1 >= 0 && str[i + palindromes_count[i]] == str[i - palindromes_count[i] - 1]) {
      ++palindromes_count[i];
    }
    if (i + palindromes_count[i] - 1 > right) {
      left = i - palindromes_count[i];
      right = i + palindromes_count[i] - 1;
    }
  }
}

int64_t ManacherAlgo(const std::string& str) {
  std::vector<int64_t> odd_palindromes(str.length()), even_palindromes(str.length());

  ManacherEven(str, even_palindromes);
  ManacherOdd(str, odd_palindromes);

  int64_t even_sum = 0;
  int64_t odd_sum = 0;

  for (int64_t i = 0; i < str.length(); i++) {
    even_sum += even_palindromes[i];
    odd_sum += odd_palindromes[i];
  }

  return even_sum + odd_sum;
}

int main() {
  std::string str;
  std::cin >> str;
  std::cout << ManacherAlgo(str);
}
