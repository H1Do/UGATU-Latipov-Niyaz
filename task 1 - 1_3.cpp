//53566299
//https://contest.yandex.ru/contest/29212/problems/1_3/
#include <iostream>

//Сокращение дробей с их выводом в консоль
void socr_drob(int ch, int zn) {
  for (int i = ch; i > 1; i--) {
    if (ch % i == 0 && zn % i == 0) {
      ch = ch / i;
      zn = zn / i;
    }
  }
  std::cout << ch << " " << zn;
}

int main() {
  int a, b, c, d;
  std::cin >> a >> b >> c >> d;
  int chislitel = a * d + c * b;
  int znamenatel = b * d;
  socr_drob(chislitel, znamenatel);
  return 0;
}
