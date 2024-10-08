#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "Figure.h"

class Rhombus : public Figure {
private:
    double* x_coords_;
    double* y_coords_;
    double x_center_;
    double y_center_;
    static const size_t NUM_VERTICES {4}; 
public:
    Rhombus();
    Rhombus(const double*, const double*);
    Rhombus(const Rhombus&);
    Rhombus(Rhombus&&) noexcept;

    ~Rhombus() override;

    void CalculateCenter() override;
    void Print(std::ostream&) const override;
    void Read(std::istream&) override;
    double Area() const override;
    double getCenterX() const;
    double getCenterY() const;
    const double* getXCoords() const;
    const double* getYCoords() const;

    Rhombus& operator=(const Figure&) override;
    Rhombus& operator=(const Rhombus&);
    Rhombus& operator=(Figure&&) noexcept override;
    Rhombus& operator=(Rhombus&&) noexcept;
    bool operator==(const Figure&) const override;
    operator double() const override;
};
#endif