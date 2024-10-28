#include "../include/Point.h"

template<Scalar T>
Point<T>::Point() : x_(T()), y_(T()) {};

template<Scalar T>
Point<T>::Point(T x, T y) : x_(x), y_(y) {};

template<Scalar T>
Point<T>::~Point() {}

template<Scalar T>
T Point<T>::getX() const {
    return x_;
}

template<Scalar T>
T Point<T>::getY() const {
    return y_;
}

template<Scalar T>
void Point<T>::setX(T x) {
    x_ = x;
}

template<Scalar T>
void Point<T>::setY(T y) {
    y_ = y;
}

template<Scalar T>
Point<T>& Point<T>::operator=(const Point& Other) {
    x_ = Other.x_;
    y_ = Other.y_;
    return *this;
}

template<Scalar T>
bool Point<T>::operator==(const Point& Other) const {
    return x_ == Other.x_ && y_ == Other.y_;
}
