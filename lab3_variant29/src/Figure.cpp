#include "Figure.h"

std::ostream& operator<<(std::ostream& os, const Figure& figure) {
    figure.Print(os);
    return os;
}

std::istream& operator>>(std::istream& is, Figure& figure) {
    figure.Read(is);
    return is;
}