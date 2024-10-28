#ifndef HEXAGON_H
#define HEXAGON_H

#include "Figure.h"
#include "Point.h"
#include <array>
#include <memory>
#include <iostream>

template<Scalar T>
class Hexagon : public Figure<T> {
private:
    static const size_t NUM_VERTICES {6}; 
    std::array<std::unique_ptr<Point<T>>, NUM_VERTICES> vertices_;
    Point<T> center_;
public:
    Hexagon();
    Hexagon(const std::array<Point<T>, NUM_VERTICES>&);
    Hexagon(const Hexagon&);
    Hexagon(Hexagon&&) noexcept;

    ~Hexagon() override;

    void CalculateCenter() override;
    void Print(std::ostream&) const override;
    void Read(std::istream&) override;
    double Area() const override;
    Point<T> GetCenter() const;

    Hexagon& operator=(const Figure<T>&) override;
    Hexagon& operator=(const Hexagon&);
    Hexagon& operator=(Figure<T>&&) noexcept override;
    Hexagon& operator=(Hexagon&&) noexcept;
    bool operator==(const Figure<T>&) const override;
    operator double() const override;
};

#include "../src/Hexagon.tpp"

#endif
