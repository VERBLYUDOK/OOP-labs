#include "../include/foo.h"

int countOnesBin(int a, int b) {
    int result = 0;
    for (int i = a; i <= b; ++i) {
	result += __builtin_popcount(i); // встроенная функция в gcc для подсчета единиц в двоичном представлении числа
    //    while (i) {
    //        if (i%2 == 1) result += 1;
    //        i /= 2;
    //    }
    }
    return result;
}