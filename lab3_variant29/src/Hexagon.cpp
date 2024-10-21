#include "Hexagon.h"

Hexagon::Hexagon()
    : x_coords_(new double[NUM_VERTICES] {}),
    y_coords_(new double[NUM_VERTICES] {}),
    x_center_ (0.0),
    y_center_ (0.0) {}

Hexagon::Hexagon(const double* x_coords, const double* y_coords)
    : x_coords_(new double[NUM_VERTICES] {}),
    y_coords_(new double[NUM_VERTICES] {}),
    x_center_(0.0),
    y_center_(0.0) 
    {
    for (size_t i {0}; i < NUM_VERTICES; ++i) {
        x_coords_[i] = x_coords[i]; 
        y_coords_[i] = y_coords[i]; 
    }
    CalculateCenter();
}

Hexagon::Hexagon(const Hexagon& Other)
    : x_coords_(new double[NUM_VERTICES] {}),
    y_coords_(new double[NUM_VERTICES] {}),
    x_center_(Other.x_center_),
    y_center_(Other.y_center_)
    {
    for (size_t i {0}; i < NUM_VERTICES; ++i) {
        x_coords_[i] = Other.x_coords_[i]; 
        y_coords_[i] = Other.y_coords_[i]; 
    }
} 

Hexagon::Hexagon(Hexagon&& Other) noexcept
    : x_coords_(Other.x_coords_),
    y_coords_(Other.y_coords_),
    x_center_(Other.x_center_),
    y_center_(Other.y_center_)
    {
    Other.x_coords_ = nullptr;
    Other.y_coords_ = nullptr;
}

Hexagon::~Hexagon() {
    delete [] x_coords_;
    delete [] y_coords_;
}

void Hexagon::CalculateCenter() {
    double area = 0.0;
    double Cx = 0.0;
    double Cy = 0.0;
    for (int i = 0; i < NUM_VERTICES; ++i) {
        int j = (i + 1) % NUM_VERTICES;
        double common = x_coords_[i] * y_coords_[j] - x_coords_[j] * y_coords_[i];
        area += common;
        Cx += (x_coords_[i] + x_coords_[j]) * common;
        Cy += (y_coords_[i] + y_coords_[j]) * common;
    }
    area /= 2.0;
    Cx /= (6.0 * area);
    Cy /= (6.0 * area);
    x_center_ = Cx;
    y_center_ = Cy;
}

void Hexagon::Print(std::ostream& os) const {
    os << "Координаты вершин 6-тиугольника:\n";
    for (size_t i {0}; i < NUM_VERTICES; ++i) {
        os << "(" << x_coords_[i] << ", " << y_coords_[i] << ")\n";
    }
    os << "Центр: (" << x_center_ << ", " << y_center_ << ")\n";
}

void Hexagon::Read(std::istream& is) {
    std::cout << "Введите координаты 6-ти вершин x y\n";
    for (size_t i {0}; i < NUM_VERTICES; ++i) {
        is >> x_coords_[i] >> y_coords_[i];
    }
    CalculateCenter();
}

double Hexagon::Area() const {
    double area = 0.0;
    for (int i = 0; i < NUM_VERTICES; ++i) {
        int j = (i + 1) % NUM_VERTICES;
        area += (x_coords_[i] * y_coords_[j]) - (x_coords_[j] * y_coords_[i]);
    }
    return std::abs(area) / 2.0;
}

Hexagon::operator double() const {
    return Area();
}

Hexagon& Hexagon::operator=(const Figure& Other) {
    if (this != &Other) {
        const Hexagon* otherHexagon = dynamic_cast<const Hexagon*>(&Other);
        if (otherHexagon) {
            *this = *otherHexagon;
        } else {
            // Объект не является Hexagon
            throw std::invalid_argument("Assigned object is not a Hexagon");
        }
    }
    return *this;
}

Hexagon& Hexagon::operator=(const Hexagon& other) {
    if (this != &other) {
        // Копируем данные
        for (size_t i = 0; i < NUM_VERTICES; ++i) {
            x_coords_[i] = other.x_coords_[i];
            y_coords_[i] = other.y_coords_[i];
        }
        x_center_ = other.x_center_;
        y_center_ = other.y_center_;
    }
    return *this;
}

Hexagon& Hexagon::operator=(Figure&& Other) noexcept{
    if (this != &Other) {
        Hexagon* otherHexagon = dynamic_cast<Hexagon*>(&Other);
        if (otherHexagon) {
            *this = std::move(*otherHexagon);
        } else {
            // Объект не является Hexagon
            throw std::invalid_argument("Assigned object is not a Hexagon");
        }
    }
    return *this;
}

Hexagon& Hexagon::operator=(Hexagon&& other) noexcept {
    if (this != &other) {
        delete[] x_coords_;
        delete[] y_coords_;

        x_coords_ = other.x_coords_;
        y_coords_ = other.y_coords_;
        x_center_ = other.x_center_;
        y_center_ = other.y_center_;

        other.x_coords_ = nullptr;
        other.y_coords_ = nullptr;
    }
    return *this;
}

bool Hexagon::operator==(const Figure& Other) const {
    const Hexagon* otherHexagon = dynamic_cast<const Hexagon*>(&Other);
    if (!otherHexagon) {
        return false;
    }
    for (size_t i {0}; i < NUM_VERTICES; ++i) {
        if (x_coords_[i] != otherHexagon->x_coords_[i] || y_coords_[i] != otherHexagon->y_coords_[i]) {
            return false;
        }
    }
    return true;
}

double Hexagon::getCenterX() const {
    return x_center_;
}

double Hexagon::getCenterY() const {
    return y_center_;
}