#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "Figure.h"
#include "Point.h"
#include <array>
#include <memory>
#include <iostream>

template<Scalar T>
class Rhombus : public Figure<T> {
private:
    static const size_t NUM_VERTICES {4}; 
    std::array<std::unique_ptr<Point<T>>, NUM_VERTICES> vertices_;
    Point<T> center_;
public:
    Rhombus();
    Rhombus(const std::array<Point<T>, NUM_VERTICES>&);
    Rhombus(const Rhombus&);
    Rhombus(Rhombus&&) noexcept;

    ~Rhombus() override;

    void CalculateCenter() override;
    void Print(std::ostream&) const override;
    void Read(std::istream&) override;
    double Area() const override;
    Point<T> GetCenter() const;

    Rhombus& operator=(const Figure<T>&) override;
    Rhombus& operator=(const Rhombus&);
    Rhombus& operator=(Figure<T>&&) noexcept override;
    Rhombus& operator=(Rhombus&&) noexcept;
    bool operator==(const Figure<T>&) const override;
    operator double() const override;
};

#include "../src/Rhombus.tpp"

#endif
