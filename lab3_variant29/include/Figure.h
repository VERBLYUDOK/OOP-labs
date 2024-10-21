#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>

class Figure {
public:
    virtual ~Figure() = default;

    virtual void CalculateCenter() = 0;
    virtual void Print(std::ostream&) const = 0;
    virtual void Read(std::istream&) = 0;
    virtual double Area() const = 0;

    
    virtual Figure& operator=(const Figure&) = 0;
    virtual Figure& operator=(Figure&&) noexcept = 0;
    virtual bool operator==(const Figure&) const = 0;
    virtual operator double() const = 0;
};
std::ostream& operator<<(std::ostream&, const Figure&);
std::istream& operator>>(std::istream&, Figure&);

#endif