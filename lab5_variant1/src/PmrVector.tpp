#include "PmrVector.h"

template<typename T>
PmrVector<T>::PmrVector(std::pmr::memory_resource* resource)
    : _data(nullptr), _size(0), _capacity(0), _allocator(resource) {}

template<typename T>
PmrVector<T>::~PmrVector() {
    for (size_t i = 0; i < _size; ++i) {
        std::allocator_traits<allocator_type>::destroy(_allocator, _data + i);
    }
    if (_data) {
        _allocator.deallocate(_data, _capacity);
    }
}

template<typename T>
void PmrVector<T>::push_back(const T& value) {
    if (_size >= _capacity) {
        reallocate(_capacity == 0 ? 1 : _capacity * 2);
    }
    std::allocator_traits<allocator_type>::construct(_allocator, _data + _size, value);
    ++_size;
}

template<typename T>
void PmrVector<T>::pop_back() {
    if (_size > 0) {
        --_size;
        std::allocator_traits<allocator_type>::destroy(_allocator, _data + _size);
    }
}

template<typename T>
T& PmrVector<T>::operator[](size_t index) {
    if (index >= _size) {
        throw std::out_of_range("Index out of range");
    }
    return _data[index];
}

template<typename T>
const T& PmrVector<T>::operator[](size_t index) const {
    if (index >= _size) {
        throw std::out_of_range("Index out of range");
    }
    return _data[index];
}

template<typename T>
size_t PmrVector<T>::size() const {
    return _size;
}

template<typename T>
size_t PmrVector<T>::capacity() const {
    return _capacity;
}

template<typename T>
T* PmrVector<T>::data() {
    return _data;
}

template<typename T>
const T* PmrVector<T>::data() const {
    return _data;
}

template<typename T>
typename PmrVector<T>::iterator PmrVector<T>::begin() {
    return iterator(_data);
}

template<typename T>
typename PmrVector<T>::iterator PmrVector<T>::end() {
    return iterator(_data + _size);
}

template<typename T>
typename PmrVector<T>::const_iterator PmrVector<T>::begin() const {
    return const_iterator(_data);
}

template<typename T>
typename PmrVector<T>::const_iterator PmrVector<T>::end() const {
    return const_iterator(_data + _size);
}

template<typename T>
void PmrVector<T>::reallocate(size_t newCapacity) {
    T* newData = _allocator.allocate(newCapacity);

    for (size_t i = 0; i < _size; ++i) {
        std::allocator_traits<allocator_type>::construct(_allocator, newData + i, std::move(_data[i]));
        std::allocator_traits<allocator_type>::destroy(_allocator, _data + i);
    }

    if (_data) {
        _allocator.deallocate(_data, _capacity);
    }

    _data = newData;
    _capacity = newCapacity;
}
