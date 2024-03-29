// https://contest.yandex.ru/contest/30914/problems/1_2
// 59019608
#include <iostream>
#include <vector>

void InsertionSort(std::vector<std::pair<int, int>> &points, int n) {
    for (int i = 1; i < n; i++) {
        auto tmp = points[i];
        int j = i - 1;
        for (; j >= 0 && tmp < points[j]; j--) {
            points[j + 1] = points[j];
        } 
        points[j + 1] = tmp;
    }
}

int main() {
  int k;
  std::cin >> k;

  std::vector<std::pair<int, int>> points;

  std::pair<int, int> input;
  for (int i = 0; i < k; i++) {
    std::cin >> input.first >> In.second;
    points.push_back(input);
  }

  InsertionSort(points, k);

  for (int i = 0; i < points.size(); i++)
    std::cout << points[i].first << ' ' << points[i].second << std::endl;
  return 0;
}
