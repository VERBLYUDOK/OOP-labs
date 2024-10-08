#ifndef HEXAGON_H
#define HEXAGON_H

#include "Figure.h"

class Hexagon : public Figure {
private:
    double* x_coords_;
    double* y_coords_;
    double x_center_;
    double y_center_;
    static const size_t NUM_VERTICES {6}; 
public:
    Hexagon();
    Hexagon(const double*, const double*);
    Hexagon(const Hexagon&);
    Hexagon(Hexagon&&) noexcept;

    ~Hexagon() override;

    void CalculateCenter() override;
    void Print(std::ostream&) const override;
    void Read(std::istream&) override;
    double Area() const override;
    double getCenterX() const;
    double getCenterY() const;

    Hexagon& operator=(const Figure&) override;
    Hexagon& operator=(Figure&&) noexcept override;
    Hexagon& operator=(const Hexagon&);
    Hexagon& operator=(Hexagon&&) noexcept;
    bool operator==(const Figure&) const override;
    operator double() const override;
};
#endif