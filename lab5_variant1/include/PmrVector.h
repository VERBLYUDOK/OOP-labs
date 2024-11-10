#ifndef PMR_VECTOR_H
#define PMR_VECTOR_H

#include <memory_resource>
#include <stdexcept>

template<typename T>
class PmrVectorIterator;

template<typename T>
class PmrVector {
public:
    using allocator_type = std::pmr::polymorphic_allocator<T>;
    using iterator = PmrVectorIterator<T>;
    using const_iterator = PmrVectorIterator<const T>;

private:
    T* _data;
    size_t _size;
    size_t _capacity;
    allocator_type _allocator;

    void reallocate(size_t);

public:
    explicit PmrVector(std::pmr::memory_resource* resource = std::pmr::get_default_resource());
    ~PmrVector();

    void push_back(const T&);
    void pop_back();
    size_t size() const;
    size_t capacity() const;
    T* data();
    const T* data() const;

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

    T& operator[](size_t);
    const T& operator[](size_t) const;
};

template<typename T>
class PmrVectorIterator {
public:
    using pointer = T*;
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using diffrence_type = ptrdiff_t;
    using reference = T&;

private:
    pointer _ptr;

public:
    PmrVectorIterator(pointer ptr = nullptr) : _ptr(ptr) {}

    reference operator*() const {return *_ptr;}
    pointer operator->() {return _ptr;}
    PmrVectorIterator& operator++() {++_ptr; return *this;}
    PmrVectorIterator& operator++(int) {PmrVectorIterator tmp = *this; ++(*this); return tmp;}

    friend bool operator==(const PmrVectorIterator& a, const PmrVectorIterator& b) {return a._ptr == b._ptr;}
    friend bool operator!=(const PmrVectorIterator& a, const PmrVectorIterator& b) {return a._ptr != b._ptr;}
};

#include "../src/PmrVector.tpp"

#endif