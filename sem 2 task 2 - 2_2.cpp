// https://contest.yandex.ru/contest/35212/problems/2_2/
// 65380975
#include <iostream>
#include <vector>

// Структура описывающая заявку
struct Application {
  int beginning, ending;

  explicit Application(const int& beginning_, const int& ending_) : beginning(beginning_), ending(ending_) { }

  friend bool operator<(const Application &first, const Application &second) {
    return first.ending < second.ending;
  }
};

template <typename T>
void SiftDown(std::vector<T>& arr, size_t size, size_t i) {
  size_t left = 2 * i + 1;
  size_t right = 2 * i + 2;
  size_t largest = i;
  if (left < size && arr[i] < arr[left]) largest = left;
  if (right < size && arr[largest] < arr[right]) largest = right;
  if (largest != i) {
    std::swap(arr[i], arr[largest]);
    SiftDown(arr, size, largest);
  }
}

// Пирамидальная сортировка
template <typename T>
void HeapSort(std::vector<T>& arr, size_t size) {
  for (size_t i = size / 2 - 1; i >= 0; i--) SiftDown(arr, size, i);
  for (size_t i = size - 1; i >= 0; i--) {
    std::swap(arr[0], arr[i]);
    SiftDown(arr, i, 0);
  }
}

// Подсчёт максимального кол-ва заявок, которые можно принять
int MaxApplications(const std::vector<Application>& Applications) {
  size_t result = 1;
  auto prev = Applications[0];

  for (size_t i = 1; i < Applications.size(); i++) {
    if (prev.ending <= Applications[i].beginning) {
      prev = Applications[i];
      result++;
    }
  }

  return result;
}

int main() {
  std::vector<Application> applications;

  int beginning, ending;
  while (std::cin >> beginning >> ending)
    applications.emplace_back(beginning, ending);

  HeapSort(applications, applications.size());

  std::cout << MaxApplications(applications) << std::endl;

  return 0;
}
