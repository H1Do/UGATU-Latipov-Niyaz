// https://contest.yandex.ru/contest/30914/problems/2_4
// 59023074
#include <iostream>
#include <vector>

// В структуре описывается позиция события и его тип (вход или выход)
struct IntervalEvent {
    int position;
    int type;
};

// Пирамидальная сортировка для массива из IntervalEvent по position
void SiftDown(std::vector<IntervalEvent>& arr, int size, int i) {
  int left = 2 * i + 1;
  int right = 2 * i + 2;
  int largest = i;
  if (left < size && arr[left].position > arr[i].position) largest = left;
  if (right < size && arr[right].position > arr[largest].position) largest = right;
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
int one_line_length(std::vector<IntervalEvent>& direct_events) {
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
    // Добавление события выхождения
    IntervalEvent IntervalFinish({input, -1});
    direct_events.push_back(IntervalFinish);
  }

  HeapSort(direct_events, direct_events.size());

  std::cout << one_line_length(direct_events) << '\n';
  return 0;
}
