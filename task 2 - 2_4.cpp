// https://contest.yandex.ru/contest/30914/problems/2_4
// 63072078
#include <iostream>
#include <vector>

// В структуре описывается позиция события и его тип (вход или выход)
struct IntervalEvent {
  int position;
  int type;

  friend bool operator<(const IntervalEvent &first, const IntervalEvent &second) {
    return first.position < second.position;
  }

  friend bool operator>(const IntervalEvent &first, const IntervalEvent &second) {
    return first.position > second.position;
  }
};

// Пирамидальная сортировка для массива из IntervalEvent по position
template <typename T>
void SiftDown(std::vector<T>& arr, int size, int i) {
  int left = 2 * i + 1;
  int right = 2 * i + 2;
  int largest = i;
  if (left < size && arr[left] > arr[i]) largest = left;
  if (right < size && arr[right] > arr[largest]) largest = right;
  if (largest != i) {
    std::swap(arr[i], arr[largest]);
    SiftDown(arr, size, largest);
  }
}

void HeapSort(std::vector<IntervalEvent>& arr, int size) {
  for (int i = size / 2 - 1; i >= 0; i--) SiftDown(arr, size, i);
  for (int i = size - 1; i >= 0; i--) {
    std::swap(arr[0], arr[i]);
    SiftDown(arr, i, 0);
  }
}

// Подсчёт длинны окрашенной в один слой
int OneLineLength(std::vector<IntervalEvent>& direct_events) {
  int ans = 0, type = 0, last_position = 0;

  for (auto event : direct_events) {
    // Проверка на нахождение в одном интервале
    if (type == 1) ans += (event.position - last_position);

    type += event.type;
    last_position = event.position;
  }
  return ans;
}

int main() {
  int k;
  std::cin >> k;
  std::vector<IntervalEvent> direct_events;

  int input;
  for (int i = 0; i < k; i++) {
    std::cin >> input;
    // Добавление события вхождения
    IntervalEvent interval_start({input, 1});
    direct_events.push_back(interval_start);

    std::cin >> input;
    // Добавление события выхода
    IntervalEvent interval_finish({input, -1});
    direct_events.push_back(interval_finish);
  }

  HeapSort(direct_events, direct_events.size());

  std::cout << OneLineLength(direct_events) << '\n';
  return 0;
}
