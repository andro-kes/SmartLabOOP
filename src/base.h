#pragma once
#include <iostream>
#include <memory>
#include "point.h"

// PointContainer для хранения точек с использованием уникальных указателей
// и односвязного списка
template<class P>
class PointContainer {
private:
    struct Node {
        std::unique_ptr<P> point;
        Node* next;
        Node(std::unique_ptr<P> p) : point(std::move(p)), next(nullptr) {}
    };

    Node* head = nullptr;
    size_t _size = 0;

public:
    PointContainer() = default;

    ~PointContainer() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Умные указатели запрещают копирование
    PointContainer(const PointContainer&) = delete;
    PointContainer& operator=(const PointContainer&) = delete;

    // Разрешаем перемещение
    PointContainer(PointContainer&& other) noexcept
        : head(other.head), _size(other._size)
    {
        other.head = nullptr;
        other._size = 0;
    }

    // Перемещающий оператор присваивания
    PointContainer& operator=(PointContainer&& other) noexcept {
        if (this != &other) {
            while (head) { Node* t = head; head = head->next; delete t; }
            head = other.head;
            _size = other._size;
            other.head = nullptr;
            other._size = 0;
        }
        return *this;
    }

    void push_back(std::unique_ptr<P> point) {
        Node* newNode = new Node(std::move(point));
        if (!head) head = newNode;
        else {
            Node* cur = head;
            while (cur->next) cur = cur->next;
            cur->next = newNode;
        }
        ++_size;
    }

    size_t size() const { return _size; }

    P& operator[](size_t index) {
        if (index >= _size) throw std::out_of_range("Index out of range");
        Node* cur = head;
        for (size_t i = 0; i < index; ++i) cur = cur->next;
        return *(cur->point);
    }

    const P& operator[](size_t index) const {
        if (index >= _size) throw std::out_of_range("Index out of range");
        Node* cur = head;
        for (size_t i = 0; i < index; ++i) cur = cur->next;
        return *(cur->point);
    }
};

template<class T>
class Figure {
public:
    using P = Point<T>;

    Figure() = default;
    virtual ~Figure() noexcept = default;

    Figure(const Figure<T>& other) {
        for (size_t i = 0; i < other.get_points_count(); ++i) {
            points.push_back(std::make_unique<P>(other.get_point(i)));
        }
    }

    Figure<T>& operator=(const Figure<T>& other) {
        if (this == &other) return *this;
        PointContainer<Point<T>> tmp;
        for (size_t i = 0; i < other.get_points_count(); ++i) {
            tmp.push_back(std::make_unique<P>(other.get_point(i)));
        }
        this->points = std::move(tmp);
        return *this;
    }

    Figure(Figure<T>&& other) noexcept = default;

    void add_point(const P& point) {
        points.push_back(std::make_unique<P>(point));
    }

    size_t get_points_count() const {
        return points.size();
    }

    const P& get_point(size_t index) const {
        return points[index];
    }

    virtual P center() const = 0;
    virtual operator double() = 0;

    friend std::ostream& operator<<(std::ostream& os, const Figure<T>& figure) {
        os << "Фигура с " << figure.points.size() << " точками:\n";
        for (size_t i = 0; i < figure.points.size(); ++i) {
            const P& p = figure.points[i];
            os << "Точка " << i << ": (" << p.getX() << ", " << p.getY() << ")\n";
        }
        return os;
    }

protected:
    PointContainer<P> points;
};