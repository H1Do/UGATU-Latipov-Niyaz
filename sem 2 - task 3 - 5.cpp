// https://contest.yandex.ru/contest/37787/problems/5/
// 68724867
#include <iostream>
#include <vector>

const int alphabet = UINT8_MAX + 1;

void BuildSufArray(const std::string& str, std::vector<int>& result) {
  int size = static_cast<int>(str.length() + 1);

  std::vector<int> cnt(alphabet);
  std::vector<int> suf(size);
  // Сортируем суффиксы по первому символу
  for (int i = 0; i < size; i++)
    cnt[static_cast<uint8_t>(str[i])]++;
  for (int i = 1; i < cnt.size(); i++)
    cnt[i] += cnt[i - 1];
  for (int i = size - 1; i >= 0; i--) {
    suf[--cnt[static_cast<uint8_t>(str[i])]] = i;
  }

  std::vector<int> pockets(size);
  std::fill(cnt.begin(), cnt.end(), 0);

  // Составляем группы суффиксов (по их порядку)
  int current_pocket = 0;
  for (int i = 0; i < size; i++) {
    if (i != 0 && str[suf[i]] != str[suf[i - 1]]) current_pocket++;
    pockets[suf[i]] = current_pocket;
    cnt[current_pocket] = i + 1;
  }

  // До конца сортируем суффиксы, используя уже отсортированные данные
  std::vector<int> temp_suf(size);
  std::vector<int> temp_pockets(size);

  for (int k = 1; k < size; k <<= 1) {
    for (int i = size - 1; i >= 0; i--)
      temp_suf[--cnt[pockets[(suf[i] - k + size) % size]]]
      = (suf[i] - k + size) % size;
    std::swap(suf, temp_suf);

    current_pocket = 0;
    std::fill(cnt.begin(), cnt.end(), 0);

    for (int i = 0; i < size; i++) {
      if (i != 0
          && (pockets[suf[i]] != pockets[suf[i - 1]]
          || pockets[(suf[i] + k) % size] != pockets[(suf[i - 1] + k) % size]))
        current_pocket++;
      temp_pockets[suf[i]] = current_pocket;
      cnt[current_pocket] = i + 1;
    }
    std::swap(pockets, temp_pockets);
  }
  result = std::move(suf);
}

void LCPKasai(const std::vector<int>& suf, const std::string& str, std::vector<int>& lcp) {
  size_t size = str.length();
  std::vector<int> inverted_suf(suf.size());

  for (int i = 0; i < size; i++) inverted_suf[suf[i]] = i;

  int cur_lcp = 0;
  for (int i = 0; i < size; i++) {
    if (inverted_suf[i] == suf.size() - 1) continue;
    int next = suf[inverted_suf[i] + 1];
    while (str[i + cur_lcp] == str[next + cur_lcp]) cur_lcp++;
    lcp[inverted_suf[i]] = cur_lcp;
    cur_lcp = std::max(0, cur_lcp - 1);
  }
}

int FindAllSubstring(const std::string& str) {
  size_t size = str.length();
  std::vector<int> suf_arr;
  BuildSufArray(str, suf_arr);

  std::vector<int> lcp(size);
  LCPKasai(suf_arr, str, lcp);

  int ans = 0;
  ans += size - suf_arr[size];
  for (int i = 0; i < size; i++) {
    ans += size - suf_arr[i];
    ans -= lcp[i];
  }

  return ans;
}

int main() {
  std::string str;
  std::cin >> str;
  std::cout << FindAllSubstring(str) << std::endl;
  return 0;
}
