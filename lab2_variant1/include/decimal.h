#ifndef DECIMAL_H
#define DECIMAL_H

#include <iostream>
#include <string>
#include <stdexcept>

class Decimal {
private:
    size_t _size;
    unsigned char *_array;

    void Fill(const Decimal&);
    void Add(const Decimal&);
    void Subtract(const Decimal&);

public:
    // Конструкторы
    Decimal(); // Конструктор по умолчанию
    Decimal(const size_t, unsigned char); // Инициализация всех элементов одним символом
    Decimal(const std::initializer_list<unsigned char>&); // Конструктор списком инициализации
    Decimal(const std::string&); // Конструктор из строки
    Decimal(const Decimal&); // Конструктор копирования
    Decimal(Decimal&&) noexcept; // Конструктор перемещения

    // Деструктор
    ~Decimal() noexcept;

    // Операторы
    Decimal& operator=(const Decimal&);
    Decimal& operator=(Decimal&&) noexcept;
    Decimal& operator+=(const Decimal&);
    Decimal operator+(const Decimal&) const;
    Decimal& operator-=(const Decimal&);
    Decimal operator-(const Decimal&) const;
    bool operator==(const Decimal&) const;
    bool operator!=(const Decimal&) const;
    bool operator<(const Decimal&) const;
    bool operator>(const Decimal&) const;
    friend std::ostream& operator<<(std::ostream&, const Decimal&);

    // Склеивает массив, превращая его в строку
    std::string ToString();
};
#endif