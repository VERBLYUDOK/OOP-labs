#include "decimal.h"

int main(){
    Decimal D1;
    std::cout << "Конструктор по умолчанию: D1 = " << D1 << std::endl;

    Decimal D2{'0', '0', '1', '2', '3', '0'};
    std::cout << "Конструктор списком инициализации {'0', '0', '1', '2', '3', '0'}: D2 = " << D2 << std::endl;

    std::string s {"020"};
    Decimal D3(s);
    std::cout << "Конструктор из строки \"020\": D3 = " << D3 << std::endl;

    Decimal D4 = D2 + D3;
    std::cout << "Конструктор копирования из суммы D2 и D3: D4 = " << D4 << std::endl;

    Decimal D5(std::move(D2));
    std::cout << "Конструктор перемещения D2: D5 = " << D5 << std::endl;

    size_t n = 5;
    Decimal D6(n, '7');
    std::cout << "Конструктор с повторяющейся цифрой 7: D6 = " << D6 << std::endl;

    D1 += D3;
    D3 += D1;
    if (D3 > D1) {
        std::cout << "D1 += D3, D3 += D1: D3 = " << D3 << std::endl;
    }
    return 0;
}