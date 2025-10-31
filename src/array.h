#include <memory>
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <type_traits>

template <typename T>
concept Arrayable = std::is_default_constructible_v<T>;

// template<class T> Array {....}
template <Arrayable T>
class Array {
public:
    Array() noexcept : _size(0), _capacity(0), _data(nullptr) {}

    // Копирующий конструктор
    Array(const Array& other) : _size(other._size), _capacity(other._capacity) {
        if (_capacity) {
            _data = std::make_unique<T[]>(_capacity);
            for (size_t i = 0; i < _size; ++i) _data[i] = other._data[i];
        }
    }

    Array& operator=(const Array& other) {
        if (this == &other) return *this;
        Array tmp(other);
        swap(tmp);
        return *this;
    }

    Array(Array&& other) noexcept : _size(other._size), _capacity(other._capacity), _data(std::move(other._data)) {
        other._size = 0;
        other._capacity = 0;
    }

    // Перемещающий оператор присваивания
    Array& operator=(Array&& other) noexcept {
        if (this == &other) return *this;
        _size = other._size;
        _capacity = other._capacity;
        _data = std::move(other._data);
        other._size = other._capacity = 0;
        return *this;
    }

    ~Array() = default;

    T& operator[](size_t idx) {
        if (idx >= _size) throw std::out_of_range("Array index out of range");
        return _data[idx];
    }
    const T& operator[](size_t idx) const {
        if (idx >= _size) throw std::out_of_range("Array index out of range");
        return _data[idx];
    }

    size_t size() const noexcept {return _size;}
    size_t capacity() const noexcept {return _capacity;}
    bool empty() const noexcept {return _size == 0;}

    void reserve(size_t new_capacity) {
        if (new_capacity <= _capacity) return;
        std::unique_ptr<T[]> new_data = std::make_unique<T[]>(new_capacity);
        for (size_t i = 0; i < _size; ++i) {
            new_data[i] = std::move(_data[i]);
        }
        _data = std::move(new_data);
        _capacity = new_capacity;
    }

    void resize(size_t new_size) {
        if (new_size > _capacity) {
            reserve(new_size);
        }
        _size = new_size;
    }

    void clear() noexcept {
        _size = 0;
    }

    void pop_back() {
        if (_size == 0) return;
        --_size;
    }

    void push_back(const T& value) {
        if (_size == _capacity) reserve(std::max<size_t>(1, _capacity * 2));
        _data[_size++] = value; 
    }

    void push_back(T&& value) {
        if (_size == _capacity) reserve(std::max<size_t>(1, _capacity * 2));
        _data[_size++] = std::move(value);
    }

    void swap(Array& other) noexcept {
        std::swap(_size, other._size);
        std::swap(_capacity, other._capacity);
        std::swap(_data, other._data);
    }

private:
    size_t _size;
    size_t _capacity;
    std::unique_ptr<T[]> _data;
};