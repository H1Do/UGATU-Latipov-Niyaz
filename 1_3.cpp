// 55374309
// https://contest.yandex.ru/contest/29212/problems/1_3/
#include <iostream>

class fraction {
public:
    int nomerator;
    int denominator;
};

// greatest common divisor calculating
int GCD(int a, int b) {
    while (a != b) {
        if (a > b)
            a = a - b;
        else
            b = b - a;
    }
    return a;
}

fraction calculating_fractions(int a, int b, int c, int d) {
    int nomerator = a * d + c * b;
    int denominator = b * d;
    int divisor = GCD(nomerator, denominator);
    nomerator /= divisor;
    denominator /= divisor;
    fraction ans;
    ans.denominator = denominator;
    ans.nomerator = nomerator;
    return ans;
}

int main() {
    int a, b, c, d;
    std::cin >> a >> b >> c >> d;

    fraction ans = calculating_fractions(a, b, c, d);
    std::cout << ans.nomerator << ' ' << ans.denominator << '\n';
    return 0;
}
