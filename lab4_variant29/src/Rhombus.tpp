#include "Rhombus.h"

template<Scalar T>
Rhombus<T>::Rhombus() : vertices_(), center_() {}

template<Scalar T>
Rhombus<T>::Rhombus(const std::array<Point<T>, NUM_VERTICES>& vertices) {
    for (size_t i = 0; i < NUM_VERTICES; ++i) {
        vertices_[i] = std::make_unique<Point<T>>(vertices[i]);
    }
    CalculateCenter();
}

template<Scalar T>
Rhombus<T>::Rhombus(const Rhombus& Other) {
    for (size_t i = 0; i < NUM_VERTICES; ++i) {
        vertices_[i] = std::make_unique<Point<T>>(*Other.vertices_[i]);
    }
    center_ = Other.center_;
}

template<Scalar T>
Rhombus<T>::Rhombus(Rhombus&& Other) noexcept {
    vertices_ = std::move(Other.vertices_);
    center_ = std::move(Other.center_);
}

template<Scalar T>
Rhombus<T>::~Rhombus() {}

template<Scalar T>
void Rhombus<T>::CalculateCenter() {
    double area = 0.0;
    T Cx = 0.0;
    T Cy = 0.0;
    for (int i = 0; i < NUM_VERTICES; ++i) {
        int j = (i + 1) % NUM_VERTICES;
        T common = vertices_[i]->getX() * vertices_[j]->getY() - vertices_[j]->getX() * vertices_[i]->getY();
        area += static_cast<double>(common);
        Cx += (vertices_[i]->getX() + vertices_[j]->getX()) * common;
        Cy += (vertices_[i]->getY() + vertices_[j]->getY()) * common;
    }
    area /= 2.0;
    Cx /= (6.0 * area);
    Cy /= (6.0 * area);
    center_.setX(Cx);
    center_.setY(Cy);
}

template<Scalar T>
void Rhombus<T>::Print(std::ostream& os) const {
    os << "Координаты вершин ромба:\n";
    for (const auto& vertex : vertices_) {
        os << "(" << vertex->getX() << ", " << vertex->getY() << ")\n";
    }
    os << "Центр: (" << center_.getX() << ", " << center_.getY() << ")\n";
}

template<Scalar T>
void Rhombus<T>::Read(std::istream& is) {
    std::cout << "Введите координаты 4-ех вершин x y\n";
    for (size_t i {0}; i < NUM_VERTICES; ++i) {
        std::cout << "Координаты точки " << i + 1 << " : ";
        T x, y;
        is >> x >> y;
        vertices_[i] = std::make_unique<Point<T>>(x, y);
    }
    CalculateCenter();
}

template<Scalar T>
double Rhombus<T>::Area() const {
    double area = 0.0;
    for (int i = 0; i < NUM_VERTICES; ++i) {
        int j = (i + 1) % NUM_VERTICES;
        T common = vertices_[i]->getX() * vertices_[j]->getY() - vertices_[j]->getX() * vertices_[i]->getY();
        area += static_cast<double>(common);
    }
    return std::abs(area) / 2.0;
}

template<Scalar T>
Point<T> Rhombus<T>::GetCenter() const {
    return center_;
}

template<Scalar T>
Rhombus<T>::operator double() const {
    return Area();
}

template<Scalar T>
Rhombus<T>& Rhombus<T>::operator=(const Figure<T>& Other) {
    if (this != &Other) {
        try {
            const Rhombus<T>& otherRhombus = dynamic_cast<const Rhombus<T>&>(Other);
            *this = otherRhombus;
        } catch (const std::bad_cast&) {
            // Объект не является Rhombus
            throw std::invalid_argument("Assigned object is not a Rhombus");
        }
    }
    return *this;
}

template<Scalar T>
Rhombus<T>& Rhombus<T>::operator=(const Rhombus<T>& Other) {
    if (this != &Other) {
        // Копируем данные
        for (size_t i = 0; i < NUM_VERTICES; ++i) {
            vertices_[i] = std::make_unique<Point<T>>(*Other.vertices_[i]);
        }
        center_ = Other.center_;
    }
    return *this;
}

template<Scalar T>
Rhombus<T>& Rhombus<T>::operator=(Figure<T>&& Other) noexcept{
    if (this != &Other) {
        try {
            Rhombus<T>& otherRhombus = dynamic_cast<Rhombus<T>&>(Other);
            *this = std::move(otherRhombus);
        } catch (const std::bad_cast&) {
            // Объект не является Rhombus
            throw std::invalid_argument("Assigned object is not a Rhombus");
        }
    }
    return *this;
}

template<Scalar T>
Rhombus<T>& Rhombus<T>::operator=(Rhombus<T>&& Other) noexcept {
    if (this != &Other) {
        vertices_ = std::move(Other.vertices_);
        center_ = std::move(Other.center_);
    }
    return *this;
}

template<Scalar T>
bool Rhombus<T>::operator==(const Figure<T>& Other) const {
    if (this != &Other) {
        try {
            const Rhombus<T>& otherRhombus = dynamic_cast<const Rhombus<T>&>(Other);
            for (size_t i {0}; i < NUM_VERTICES; ++i) {
                if (!(*vertices_[i] == *otherRhombus.vertices_[i])) {
                    return false;
                }
            }
        } catch (const std::bad_cast&) {
            // Объект не является Rhombus
            return false;
        }
    }
    return true;
}
