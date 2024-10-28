#include <iostream>
#include "include/foo.h"

int main() {
    int a, b;
    std::cout << "Введите границы последовательности чисел от a до b включительно\na = ";
    std::cin >> a;
    std::cout << "b = ";
    std::cin >> b;
    int count = countOnesBin(a, b);
    std::cout << "Сумма единиц в двоичном представлении всех чисел последовательности равна " << count << '\n';
    return 0;
}