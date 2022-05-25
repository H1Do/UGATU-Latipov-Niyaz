// https://contest.yandex.ru/contest/37787/problems/1/
// 68217255
#include <iostream>
#include <vector>

void Z(const std::string& str, std::vector<int>& z) {
  for (int i = 1, left = 0, right = 0; i < str.length(); i++) {
    if (i <= right)
      z[i] = std::min(right - i + 1, z[i - left]);
    while (i + z[i] < str.length() && str[z[i]] == str[i + z[i]])
      z[i]++;
    if (i + z[i] - 1 > right)
      left = i, right = i + z[i] - 1;
  }
}

void TemplateFinder(const std::string& pattern, const std::string& str, std::vector<size_t>& result) {
  auto string = pattern + '$' + str;
  std::vector<int> z(string.length());
  Z(string, z);

  for (int i = 1; i < string.length(); i++) {
    if (z[i] == pattern.length()) {
      result.push_back(i - pattern.length() - 1);
    }
  }
}

int main() {
  std::string pattern;
  std::string str;
  std::cin >> pattern >> str;

  std::vector<size_t> result;
  TemplateFinder(pattern, str, result);

  for (auto i : result) std::cout << i << ' ';

  std::cout << std::endl;
  return 0;
}
