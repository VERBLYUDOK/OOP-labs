#include "../include/foo.h"

int countOnesBin(int a, int b) {
    int result = 0;
    for (int i = a; i <= b; ++i) {
	result += __builtin_popcount(i); // встроенная функция в gcc для подсчета единиц в двоичном представлении числа
    }
    return result;
}