#include "decimal.h"

Decimal::Decimal(): _size{0}, _array{nullptr} {}
Decimal::Decimal(const size_t n, unsigned char c) {
    if (n == 0) {
        throw std::invalid_argument("Размер массива не может быть нулевым");
    }
    if (!std::isdigit(c)) {
        throw std::invalid_argument("Символ должен быть десятичной цифрой");
    }

    _size = n;
    _array = new unsigned char[_size];
    size_t i{0};
    while (i < _size) {
        _array[i++] = c - '0';
    }
}
Decimal::Decimal(const std::initializer_list<unsigned char>& list) {
    if (list.size() == 0) {
        throw std::invalid_argument("Нельзя создать Decimal с пустым списком");
    }
    // Проверяем, что все символы списка являются цифрами
    for (auto c : list) {
        if (!std::isdigit(c)) {
            throw std::invalid_argument("Список содержит недопустимый символ: все элементы должны быть десятичными цифрами");
        }
    }

    size_t realSize = list.size();
    // Не учитываем ведущие нули с начала списка
    auto it = list.begin();
    while (realSize > 1 && *(it) == '0') {
        --realSize;
        ++it;
    }

    _size = realSize;
    _array = new unsigned char[_size];
    size_t i{_size - 1};
    do {
        _array[i--] = *(it++) - '0';
    } while (it != list.end());
}
Decimal::Decimal(const std::string& str) {
    if (str.empty()) {
        throw std::invalid_argument("Пустая строка не является допустимым числом");
    }
    // Проверяем, что все символы строки являются цифрами
    for (char c : str) {
        if (!std::isdigit(c)) {
            throw std::invalid_argument("Строка содержит недопустимый символ: все символы должны быть десятичными цифрами");
        }
    }

    // Найдём реальный размер числа без ведущих нулей
    size_t realSize = str.size();
    while (realSize > 1 && str[str.size() - realSize] == '0') {
        --realSize;
    }

    _size = realSize;
    _array = new unsigned char[_size];
    for (size_t i = 0; i < _size; ++i) {
        _array[i] = str[str.size() - i - 1] - '0';
    }
}
Decimal::Decimal(const Decimal& Other) {
    _size = Other._size;
    _array = new unsigned char[_size];
    for (size_t i = 0; i < _size; ++i) {
        _array[i] = Other._array[i];
    }
}
Decimal::Decimal(Decimal&& Other) noexcept {
    _size = Other._size;
    _array = Other._array;

    Other._size = 0;
    Other._array = nullptr;
}
Decimal::~Decimal() noexcept {
    if (_size > 0) {
        _size = 0;
        delete [] _array;
        _array = nullptr;
    }
}
Decimal& Decimal::operator=(const Decimal& Other) {
    this->Fill(Other);
    return *this;
}
Decimal& Decimal::operator=(Decimal&& Other) noexcept {
    delete[] _array;
    _size = Other._size;
    _array = Other._array;
    Other._size = 0;
    Other._array = nullptr;
    return *this;
}
Decimal& Decimal::operator+=(const Decimal& Other) {
    // Если this пуст, то просто копируем Other в this
    if (this->_size == 0) {
        this->Fill(Other);
        return *this;
    }
    this->Add(Other);
    return *this;
}
Decimal Decimal::operator+(const Decimal& Other) const {
    Decimal NewDecimal(*this);
    NewDecimal.Add(Other);
    return NewDecimal;
}
Decimal Decimal::operator-(const Decimal& Other) const {
    Decimal NewDecimal(*this);
    NewDecimal.Subtract(Other);
    return NewDecimal;
}
Decimal& Decimal::operator-=(const Decimal& Other) {
    this->Subtract(Other);
    return *this;
}
bool Decimal::operator==(const Decimal& Other) const {
    if (this->_size != Other._size) {
        return false;
    }

    for (size_t i = 0; i < this->_size; ++i) {
        if (this->_array[i] != Other._array[i]) {
            return false;
        }
    }

    return true;
}
bool Decimal::operator!=(const Decimal& Other) const {
    return !(*this == Other);
}
bool Decimal::operator<(const Decimal& Other) const {
    if (this->_size < Other._size) {
        return true;
    } else if (this->_size > Other._size) {
        return false;
    }

    // Если размеры равны, сравниваем цифры начиная с конца (старшие разряды)
    for (size_t i = this->_size; i > 0; --i) {
        if (this->_array[i - 1] < Other._array[i - 1]) {
            return true;
        } else if (this->_array[i - 1] > Other._array[i - 1]) {
            return false;
        }
    }

    return false;
}
bool Decimal::operator>(const Decimal& Other) const {
    return Other < *this;
}
void Decimal::Subtract(const Decimal& Other) {
    if (this->_size < Other._size) {
        throw std::invalid_argument("Нельзя вычесть из меньшего числа большее");
    }

    unsigned char borrow = 0;  // Запоминаем занимали ли

    for (size_t i = 0; i < this->_size; ++i) {
        unsigned char digit1 = this->_array[i];
        unsigned char digit2 = (i < Other._size) ? Other._array[i] : 0;

        if (digit1 < digit2 + borrow) {
            this->_array[i] = digit1 + 10 - digit2 - borrow;  // Занимаем из следующего разряда
            borrow = 1;  // В следующем разряде занимаем
        } else {
            this->_array[i] = digit1 - digit2 - borrow;
            borrow = 0;
        }
    }

    // Убираем ведущие нули
    while (this->_size > 1 && this->_array[this->_size - 1] == 0) {
        --this->_size;
    }
}
void Decimal::Add(const Decimal& Other) {
    if (this->_size < Other._size) {
        unsigned char* newArray = new unsigned char[Other._size];

        // Копируем старый массив this в новый массив с нулями
        for (size_t i = 0; i < this->_size; ++i) {
            newArray[i] = this->_array[i];
        }
        for (size_t i = this->_size; i < Other._size; ++i) {
            newArray[i] = 0;
        }

        // Освобождаем старую память
        delete[] this->_array;

        // Обновляем this->_array
        this->_array = newArray;
        this->_size = Other._size;
    }

    // Переменная для переноса
    unsigned char carry = 0;

    for (size_t i = 0; i < this->_size; ++i) {
        unsigned char sum = this->_array[i] + (i < Other._size ? Other._array[i] : 0) + carry;
        if (sum > 9) {
            this->_array[i] = sum - 10;
            carry = 1;
        } else {
            this->_array[i] = sum;
            carry = 0;
        }
    }

    // Если есть перенос после последней цифры
    if (carry > 0) {
        // Расширяем массив и добавляем перенос
        unsigned char* newArray = new unsigned char[this->_size + 1];
        for (size_t i = 0; i < this->_size; ++i) {
            newArray[i] = this->_array[i];
        }
        newArray[this->_size] = '1';
        ++this->_size;

        // Освобождаем старую память и обновляем указатель
        delete[] this->_array;
        this->_array = newArray;
    }
}
void Decimal::Fill(const Decimal& Other) {
    delete[] this->_array;
    this->_size = Other._size;
    this->_array = new unsigned char[this->_size];
    for (size_t i = 0; i < this->_size; ++i) {
        this->_array[i] = Other._array[i];
    }
}
std::ostream& operator<<(std::ostream& stream, const Decimal& Dec) {
    // Выводим число начиная с самого старшего разряда
    for (size_t i = Dec._size; i > 0; --i) {
        stream << static_cast<char>(Dec._array[i - 1] + '0');  // Преобразуем цифру в символ
    }

    return stream;
}
std::string Decimal::ToString() {
    std::string s{""};
    for (size_t i = this->_size; i > 0; --i) {
        s += this->_array[i - 1] + '0';
    }
    return s;
}