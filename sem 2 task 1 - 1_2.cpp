// https://contest.yandex.ru/contest/35212/problems/1
// 65825689
#include <iostream>

struct Hash1 {
  unsigned int operator()(const std::string& input_string, unsigned int max) const {
    unsigned int hash = 0;
    for (auto symbol : input_string) hash = (hash * 761 + symbol) % max;
    return hash;
  }
};

struct Hash2 {
  unsigned int operator()(const std::string& input_string, unsigned int max) const {
    unsigned int hash = 1;
    for (auto symbol : input_string) hash = (hash * 383 + symbol) % max;
    return (hash * 2 + 1) % max;
  }
};

// ХешТаблица
template <typename T, typename THash1 = Hash1, typename THash2 = Hash2>
class HashTable {
 private:
  struct HashNode {
    T value;
    bool is_deleted;
    explicit HashNode(const T& value_)
        : value(std::move(value_)), is_deleted(false) {}
  };

  unsigned int buffer_size;
  unsigned int buffer_occupancy;

  HashNode** buffer;

  // Функция рехеширования (с двойным увеличением объема)
  void Rebuild() {
    buffer_size *= 2;
    buffer_occupancy = 0;

    auto** temp_buffer = new HashNode* [buffer_size] { nullptr };

    std::swap(buffer, temp_buffer);

    for (int i = 0; i < buffer_size / 2; i++) {
      if (temp_buffer[i] && !temp_buffer[i]->is_deleted)
        Insert(temp_buffer[i]->value);
      delete temp_buffer[i];
    }
    delete[] temp_buffer;
  }

  // Функция двойного хеширования
  unsigned int Hash(unsigned int hash1_result, unsigned int hash2_result, unsigned int i) {
    return (hash1_result + i * hash2_result) % buffer_size;
  }

 public:
  // Конструктор
  HashTable() : buffer_size(8), buffer_occupancy(0) {
    buffer = new HashNode* [buffer_size] { nullptr };
  }

  // Деструктор
  ~HashTable() {
    for (int i = 0; i < buffer_size; i++)
      if (!buffer[i]) delete buffer[i];
    delete[] buffer;
  }

  // Конструктор копирования
  HashTable(const HashTable& other) : buffer_size(other.buffer_size),
                                      buffer_occupancy(other.buffer_occupancy),
                                      buffer(other.buffer) { }

  // Конструктор перемещения
  HashTable(HashTable&& other) noexcept {
    buffer_size = other.buffer_size;
    buffer_occupancy = other.buffer_occupancy;
    buffer = other.buffer;
    other.buffer_size = 0;
    other.buffer_occupancy = 0;
    other.buffer = nullptr;
  }

  // Оператор копирования
  HashTable& operator=(const HashTable& other) {
    *this = HashTable(other);
    return *this;
  }

  // Оператор перемещения
  HashTable& operator=(HashTable&& other) noexcept {
    std::swap(buffer_size, other.buffer_size);
    std::swap(buffer_occupancy, buffer_occupancy);
    std::swap(buffer, buffer);
    return *this;
  }

  // Функция ввода данных
  bool Insert(const T& value, const THash1& HashF1 = THash1(),
              const THash2& HashF2 = THash2()) {

    if (Find(value)) return false;
    if ((static_cast<double>(buffer_occupancy) /
        static_cast<double>(buffer_size)) >= (3.0 / 4.0))
      Rebuild();

    unsigned int hash1 = HashF1(value, buffer_size);
    unsigned int hash2 = HashF2(value, buffer_size);
    unsigned int hash = Hash(hash1, hash2, 0);

    for (unsigned int i = 1; i < buffer_size; i++) {
      if (buffer[hash] == nullptr || buffer[hash]->is_deleted) {
        buffer[hash] = new HashNode(value);
        buffer_occupancy++;
        return true;
      }

      hash = Hash(hash1, hash2, i);
    }
    return false;
  }

  // Функция удаления данных
  bool Delete(const T& value, const THash1& HashF1 = THash1(),
              const THash2& HashF2 = THash2()) {

    unsigned int hash1 = HashF1(value, buffer_size);
    unsigned int hash2 = HashF2(value, buffer_size);
    unsigned int hash = Hash(hash1, hash2, 0);

    for (unsigned int i = 1; buffer[hash] != nullptr; i++) {
      if (buffer[hash]->value == value && !buffer[hash]->is_deleted) {
        buffer[hash]->is_deleted = true;
        buffer_occupancy--;
        return true;
      }
      hash = Hash(hash1, hash2, i);
    }
    return false;
  }

  // Функция поиска данных
  bool Find(const T& value, const THash1& HashF1 = THash1(),
            const THash2& HashF2 = THash2()) {

    unsigned int hash1 = HashF1(value, buffer_size);
    unsigned int hash2 = HashF2(value, buffer_size);
    unsigned int hash = Hash(hash1, hash2, 0);

    for (unsigned int i = 1; buffer[hash] != nullptr && i < buffer_size; i++) {
      if (buffer[hash]->value == value && !buffer[hash]->is_deleted)
        return true;

      hash = Hash(hash1, hash2, i);
    }
    return false;
  }
};


int main() {
  HashTable<std::string> hash_table;

  std::string sign, value;
  while (std::cin >> sign >> value) {
    if (sign == "+")
      std::cout << (hash_table.Insert(value) ? "OK" : "FAIL") << std::endl;
    else if (sign == "-")
      std::cout << (hash_table.Delete(value) ? "OK" : "FAIL") << std::endl;
    else if (sign == "?")
      std::cout << (hash_table.Find(value) ? "OK" : "FAIL") << std::endl;
  }

  return 0;
}
