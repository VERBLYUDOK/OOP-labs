template<typename T>
Array<T>::Array() : size_(0), capacity_(1), data_(std::make_shared<T[]>(1)) {}

template<typename T>
Array<T>::Array(size_t capacity) : size_(0), capacity_(capacity), data_(std::make_shared<T[]>(capacity)) {}

template<typename T>
Array<T>::Array(const Array& other)
    : size_(other.size_), capacity_(other.capacity_), data_(std::make_shared<T[]>(other.capacity_)) {
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = other.data_[i];
    }
}

template<typename T>
Array<T>::Array(Array&& other) noexcept
    : size_(other.size_), capacity_(other.capacity_), data_(std::move(other.data_)) {
    other.size_ = 0;
    other.capacity_ = 0;
}

template<typename T>
void Array<T>::PushBack(const T& item) {
    if (size_ == capacity_) {
        Resize(capacity_ * 2);
    }
    data_[size_] = item;
    ++size_;
}

template<typename T>
void Array<T>::PushBack(T&& item) {
    if (size_ == capacity_) {
        Resize(capacity_ * 2);
    }
    data_[size_] = std::move(item);
    ++size_;
}

template<typename T>
void Array<T>::RemoveAt(size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    for (size_t i = index; i < size_ - 1; ++i) {
        data_[i] = std::move(data_[i + 1]);
    }
    --size_;
}

template<typename T>
T& Array<T>::operator[](size_t index) {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

template<typename T>
const T& Array<T>::operator[](size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[index];
}

template<typename T>
Array<T>& Array<T>::operator=(const Array& Other) {
    if (this != &Other) {
        size_ = Other.size_;
        capacity_ = Other.capacity_;
        data_ = std::make_shared<T[]>(capacity_);
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = Other.data_[i];
        }
    }
    return *this;
}

template<typename T>
Array<T>& Array<T>::operator=(Array&& other) noexcept {
    if (this != &other) {
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = std::move(other.data_);
        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}

template<typename T>
void Array<T>::Resize(size_t new_capacity) {
    std::shared_ptr<T[]> new_data = std::make_shared<T[]>(new_capacity);
    for (size_t i = 0; i < size_; ++i) {
        new_data[i] = std::move(data_[i]);
    }
    capacity_ = new_capacity;
    data_ = std::move(new_data);
}

template<typename T>
size_t Array<T>::Size() const {
    return size_;
}

template<typename T>
size_t Array<T>::Capacity() const {
    return capacity_;
}
