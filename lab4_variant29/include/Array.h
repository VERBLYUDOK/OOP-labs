#ifndef ARRAY_H
#define ARRAY_H

#include <memory>
#include <stdexcept>

template<typename T>
class Array {
private:
    void Resize(size_t);

    size_t size_;
    size_t capacity_;
    std::shared_ptr<T[]> data_;
public:
    Array();
    explicit Array(size_t);
    Array(const Array&);
    Array(Array&&) noexcept;
    ~Array() = default;

    void PushBack(const T&);
    void PushBack(T&&);
    void RemoveAt(size_t);
    size_t Size() const;
    size_t Capacity() const;

    T& operator[](size_t);
    const T& operator[](size_t) const;
    Array& operator=(const Array&);
    Array& operator=(Array&&) noexcept;
};

#include "../src/Array.tpp"

#endif
