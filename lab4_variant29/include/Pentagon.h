#ifndef PENTAGON_H
#define PENTAGON_H

#include "Figure.h"
#include "Point.h"
#include <array>
#include <memory>
#include <iostream>

template<Scalar T>
class Pentagon : public Figure<T> {
private:
    static const size_t NUM_VERTICES {5}; 
    std::array<std::unique_ptr<Point<T>>, NUM_VERTICES> vertices_;
    Point<T> center_;
public:
    Pentagon();
    Pentagon(const std::array<Point<T>, NUM_VERTICES>&);
    Pentagon(const Pentagon&);
    Pentagon(Pentagon&&) noexcept;

    ~Pentagon() override;

    void CalculateCenter() override;
    void Print(std::ostream&) const override;
    void Read(std::istream&) override;
    double Area() const override;
    Point<T> GetCenter() const;

    Pentagon& operator=(const Figure<T>&) override;
    Pentagon& operator=(const Pentagon&);
    Pentagon& operator=(Figure<T>&&) noexcept override;
    Pentagon& operator=(Pentagon&&) noexcept;
    bool operator==(const Figure<T>&) const override;
    operator double() const override;
};

#include "../src/Pentagon.tpp"

#endif
