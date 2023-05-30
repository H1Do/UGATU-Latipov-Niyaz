// https://contest.yandex.ru/contest/37787/problems/2_1
// 68765005	
#include <iostream>
#include <vector>

std::string StrByPi(const std::vector<int>& pi) {
  std::string str = !pi.empty() ? "a" : "";

  std::vector<int> spent_chars(26);
  char cur_char;
  for (int i = 1; i < pi.size(); i++) {
    if (pi[i] == 0) {
      spent_chars.assign(26, 0);
      cur_char = 'b';

      for (int j = pi[i - 1]; j > 0; j = pi[j - 1])
        spent_chars[str[j] - 'a'] = 1;

      while (spent_chars[cur_char - 'a']) cur_char++;
      str += cur_char;
    } else {
      str += str[pi[i] - 1];
    }
  }
  return str;
}

int main() {
  std::vector<int> pi;

  int number;
  while (std::cin >> number)
    pi.push_back(number);

  std::cout << StrByPi(pi); << std::endl;
  return 0;
}
