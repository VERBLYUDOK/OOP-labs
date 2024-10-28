#ifndef PENTAGON_H
#define PENTAGON_H

#include "Figure.h"

class Pentagon : public Figure {
private:
    double* x_coords_;
    double* y_coords_;
    double x_center_;
    double y_center_;
    static const size_t NUM_VERTICES {5}; 
public:
    Pentagon();
    Pentagon(const double*, const double*);
    Pentagon(const Pentagon&);
    Pentagon(Pentagon&&) noexcept;

    ~Pentagon() override;

    void CalculateCenter() override;
    void Print(std::ostream&) const override;
    void Read(std::istream&) override;
    double Area() const override;
    double getCenterX() const;
    double getCenterY() const;

    Pentagon& operator=(const Figure&) override;
    Pentagon& operator=(Figure&&) noexcept override;
    Pentagon& operator=(const Pentagon&);
    Pentagon& operator=(Pentagon&&) noexcept;
    bool operator==(const Figure&) const override;
    operator double() const override;
};
#endif