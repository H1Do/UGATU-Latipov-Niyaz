// Положение существенно улучшилось, однако теперь просто валиться на 7 тесте. Пытался поиграться с коэффициентами,
// соблюдая (h1 + i * h2) % M где M (размер таблицы) степень двойки, а h2 всегда нечетная, однако
// никакого прогресса не вижу.
// https://contest.yandex.ru/contest/35212/problems/1/?success=65721542#194179/2016_11_21/YiZ2Xj7kse
// 65721512
#include <iostream>
#include <utility>

// Первая хеш функция (Методом Горнера)
unsigned int Hash1(const std::string& input_string, unsigned int max) {
  unsigned int hash = 0;
  for (auto symbol : input_string)
    hash = (hash * 7 + symbol) % max;
  return hash;
}

// Вторая хеш функция (возвращает исключительно нечетные числа)
unsigned int Hash2(const std::string& input_string, unsigned int max) {
  unsigned int hash = 1;
  for (auto symbol : input_string)
    hash = (hash * 3 + symbol) % max;
  return (hash * 2 + 1) % max;
}

// Функция двойного хеширования
unsigned int Hash(unsigned int hash1, unsigned int hash2, unsigned int i, unsigned int max) {
  return (hash1 + i * hash2) % max;
}

// ХешТаблица
class HashTable {
 private:

  struct HashNode {
    std::string value;
    bool is_it_deleted;
    explicit HashNode(std::string value_) : value(std::move(value_)), is_it_deleted(false) { }
  };

  unsigned int buffer_size;
  unsigned int buffer_occupancy;

  HashNode** buffer;

  // Функция рехеширования (с двойным увеличением объема)
  void Rebuild() {
    unsigned int temp_size = buffer_size;
    buffer_size *= 2;
    buffer_occupancy = 0;

    auto** temp_buffer = new HashNode*[buffer_size]{nullptr};

    std::swap(buffer, temp_buffer);

    for (int i = 0; i < temp_size; i++) {
      if (temp_buffer[i] && !temp_buffer[i]->is_it_deleted) {
        Insert(temp_buffer[i]->value);
        delete temp_buffer[i];
      }
    }
    delete[] temp_buffer;
  }

 public:
  // Конструктор
  HashTable() {
    buffer_size = 8;
    buffer_occupancy = 0;

    buffer = new HashNode*[buffer_size]{nullptr};
  }

  // Деструктор
  ~HashTable() {
    for (int i = 0; i < buffer_size; i++)
      if (!buffer[i])
        delete buffer[i];
    delete[] buffer;
  }

  // Функция ввода данных
  bool Insert(const std::string& value) {
    if ((static_cast<double>(buffer_occupancy) / static_cast<double>(buffer_size)) >= (3.0 / 4.0))
      Rebuild();

    unsigned int hash1 = Hash1(value, buffer_size);
    unsigned int hash2 = Hash2(value, buffer_size);
    unsigned int hash = Hash(hash1, hash2, 0, buffer_size);

    unsigned int i = 0;
    unsigned int temp = 0;

    while (buffer[hash] != nullptr) {
      if (buffer[hash]->value == value && !buffer[hash]->is_it_deleted)
        return false;
      if (buffer[hash]->is_it_deleted && !temp)
        temp = hash;

      hash = Hash(hash1, hash2, i, buffer_size);
      i++;
    }

    if (!temp) {
      buffer[hash] = new HashNode(value);
    } else {
      buffer[temp]->value = value;
      buffer[temp]->is_it_deleted = false;
    }

    buffer_occupancy++;
    return true;
  }

  // Функция удаления данных
  bool Delete(const std::string& value) {
    unsigned int hash1 = Hash1(value, buffer_size);
    unsigned int hash2 = Hash2(value, buffer_size);
    unsigned int hash = Hash(hash1, hash2, 0, buffer_size);
    unsigned int i = 0;

    while (buffer[hash] != nullptr) {
      if (buffer[hash]->value == value && !buffer[hash]->is_it_deleted) {
        buffer[hash]->is_it_deleted = true;
        buffer_occupancy--;
        return true;
      }
      hash = Hash(hash1, hash2, i, buffer_size);
      i++;
    }

    return false;
  }

  // Функция поиска данных
  bool Find(const std::string& value) {
    unsigned int hash1 = Hash1(value, buffer_size);
    unsigned int hash2 = Hash2(value, buffer_size);
    unsigned int hash = Hash(hash1, hash2, 0, buffer_size);
    unsigned int i = 0;

    while (buffer[hash] != nullptr) {
      if (buffer[hash]->value == value && !buffer[hash]->is_it_deleted) {
        return true;
      }
      hash = Hash(hash1, hash2, i, buffer_size);
      i++;
    }
    return false;
  }

  void PrintAllElements() {
    for (unsigned int i = 0; i < buffer_size; i++)
      std::cout << i << ' ' << (buffer[i] ? buffer[i]->value : "-1") << std::endl;
    std::cout << static_cast<double>(buffer_occupancy) / static_cast<double>(buffer_size);
  }
};

int main() {
  HashTable hash_table;

  std::string sign, value;
  while (std::cin >> sign >> value) {
    if (sign == "+")
      std::cout << (hash_table.Insert(value) ? "OK" : "FAIL") << std::endl;
    else if (sign == "-")
      std::cout << (hash_table.Delete(value) ? "OK" : "FAIL") << std::endl;
    else if (sign == "?")
      std::cout << (hash_table.Find(value) ? "OK" : "FAIL") << std::endl;
    // hash_table.PrintAllElements();
  }
}
