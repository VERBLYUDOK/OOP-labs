#include "Pentagon.h"

Pentagon::Pentagon()
    : x_coords_(new double[NUM_VERTICES] {}),
    y_coords_(new double[NUM_VERTICES] {}),
    x_center_ (0.0),
    y_center_ (0.0) {}

Pentagon::Pentagon(const double* x_coords, const double* y_coords)
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

Pentagon::Pentagon(const Pentagon& Other)
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

Pentagon::Pentagon(Pentagon&& Other) noexcept
    : x_coords_(Other.x_coords_),
    y_coords_(Other.y_coords_),
    x_center_(Other.x_center_),
    y_center_(Other.y_center_)
    {
    Other.x_coords_ = nullptr;
    Other.y_coords_ = nullptr;
}

Pentagon::~Pentagon() {
    delete [] x_coords_;
    delete [] y_coords_;
}

void Pentagon::CalculateCenter() {
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

void Pentagon::Print(std::ostream& os) const {
    os << "Координаты вершин 5-тиугольника:\n";
    for (size_t i {0}; i < NUM_VERTICES; ++i) {
        os << "(" << x_coords_[i] << ", " << y_coords_[i] << ")\n";
    }
    os << "Центр: (" << x_center_ << ", " << y_center_ << ")\n";
}

void Pentagon::Read(std::istream& is) {
    std::cout << "Введите координаты 5-ти вершин x y\n";
    for (size_t i {0}; i < NUM_VERTICES; ++i) {
        is >> x_coords_[i] >> y_coords_[i];
    }
    CalculateCenter();
}

double Pentagon::Area() const {
    double area = 0.0;
    for (int i = 0; i < NUM_VERTICES; ++i) {
        int j = (i + 1) % NUM_VERTICES;
        area += (x_coords_[i] * y_coords_[j]) - (x_coords_[j] * y_coords_[i]);
    }
    return std::abs(area) / 2.0;
}

Pentagon::operator double() const {
    return Area();
}

Pentagon& Pentagon::operator=(const Figure& Other) {
    if (this != &Other) {
        const Pentagon* otherPentagon = dynamic_cast<const Pentagon*>(&Other);
        if (otherPentagon) {
            *this = *otherPentagon;
        } else {
            // Объект не является Pentagon
            throw std::invalid_argument("Assigned object is not a Pentagon");
        }
    }
    return *this;
}

Pentagon& Pentagon::operator=(const Pentagon& other) {
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

Pentagon& Pentagon::operator=(Figure&& Other) noexcept{
    if (this != &Other) {
        Pentagon* otherPentagon = dynamic_cast<Pentagon*>(&Other);
        if (otherPentagon) {
            *this = std::move(*otherPentagon);
        } else {
            // Объект не является Pentagon
            throw std::invalid_argument("Assigned object is not a Pentagon");
        }
    }
    return *this;
}

Pentagon& Pentagon::operator=(Pentagon&& other) noexcept {
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

bool Pentagon::operator==(const Figure& Other) const {
    const Pentagon* otherPentagon = dynamic_cast<const Pentagon*>(&Other);
    if (!otherPentagon) {
        return false;
    }
    for (size_t i {0}; i < NUM_VERTICES; ++i) {
        if (x_coords_[i] != otherPentagon->x_coords_[i] || y_coords_[i] != otherPentagon->y_coords_[i]) {
            return false;
        }
    }
    return true;
}

double Pentagon::getCenterX() const {
    return x_center_;
}

double Pentagon::getCenterY() const {
    return y_center_;
}

const double* Pentagon::getXCoords() const {
    return x_coords_;
}

const double* Pentagon::getYCoords() const {
    return y_coords_;
}