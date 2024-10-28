#ifndef POINT_H
#define POINT_H

#include <concepts>

template<typename T>
concept Scalar = std::is_scalar_v<T>;

template<Scalar T>
class Point {
private:
    T x_;
    T y_;
public:
    Point();
    Point(T x, T y);

    ~Point();

    T getX() const;
    T getY() const;
    void setX(T x);
    void setY(T y);

    Point& operator=(const Point&);
    bool operator==(const Point&) const;
};

#include "../src/Point.tpp"

#endif
