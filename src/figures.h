#include <iostream>
#include "base.h"

template<class T>
class Pentagon : public Figure<T> {
public:
    Pentagon() {std::cout << "Введите точки для 5-угольника:\n";}
    Pentagon(const Pentagon<T>& other) : Figure<T>() {  
        PointContainer<Point<T>> tmp;
        for (size_t i = 0; i < other.get_points_count(); ++i) {
            tmp.push_back(std::make_unique<Point<T>>(other.get_point(i)));
        }
        this->points = std::move(tmp);
    }
    Pentagon(Pentagon<T>&& other) noexcept = default;

    Point<T> center() const {
        // Берем среднее всех координат
        T sum_x = 0, sum_y = 0;
        size_t count = 0;
        
        for (size_t i = 0; i < this->points.size(); ++i) {
            if (i % 2 == 0) {
                sum_x += this->points[i].getX();
                sum_y += this->points[i].getY();
                count++;
            }
        }
        
        if (count == 0) {
            return Point<T>(this->points[0].getX(), this->points[0].getY());
        }
        
        return Point<T>(sum_x / count, sum_y / count);
    }

    // Вычисляем площадь в приведении к типу double
    operator double() {
        const size_t n = this->get_points_count();
        double sum = 0.0;
        for (size_t i = 0; i < n; ++i) {
            const auto &p = this->get_point(i);
            const auto &q = this->get_point((i + 1) % n);
            double xi = static_cast<double>(p.getX());
            double yi = static_cast<double>(p.getY());
            double xj = static_cast<double>(q.getX());
            double yj = static_cast<double>(q.getY());
            sum += xi * yj - xj * yi;
        }
        return std::abs(sum) * 0.5;
    }

    friend std::ostream& operator<<(std::ostream& os, const Pentagon<T>& figure) {
        os << "Фигура с " << figure.get_points_count() << " точками:\n";
        for (size_t i = 0; i < figure.get_points_count(); ++i) {
            const auto& p = figure.get_point(i);
            os << "Точка " << i << ": (" << p.getX() << ", " << p.getY() << ")\n";
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Pentagon<T>& pentagon) {
        for (int i = 0; i < 5; ++i) {
            T x, y;
            if (!(is >> x >> y)) break;
            pentagon.add_point(Point<T>(x, y));
        }
        return is;
    }
};


template<class T>
class Trapezoid : public Figure<T> {
public:
    Trapezoid() { std::cout << "Введите точки для трапеции\n"; }
    Trapezoid(const Trapezoid<T>& other) : Figure<T>() {  
        PointContainer<Point<T>> tmp;
        for (size_t i = 0; i < other.get_points_count(); ++i) {
            tmp.push_back(std::make_unique<Point<T>>(other.get_point(i)));
        }
        this->points = std::move(tmp);
    }

    Point<T> center() const {
        double sum_x = 0, sum_y = 0;
        for (size_t i = 0; i < 4; ++i) {
            sum_x += this->points[i].getX();
            sum_y += this->points[i].getY();
        }
        return Point<T>(sum_x / 4, sum_y / 4);
    }

    operator double() {
        const size_t n = this->get_points_count();
        double sum = 0.0;
        for (size_t i = 0; i < n; ++i) {
            const auto &p = this->get_point(i);
            const auto &q = this->get_point((i + 1) % n);
            double xi = static_cast<double>(p.getX());
            double yi = static_cast<double>(p.getY());
            double xj = static_cast<double>(q.getX());
            double yj = static_cast<double>(q.getY());
            sum += xi * yj - xj * yi;
        }
        return std::abs(sum) * 0.5;
    }

    friend std::ostream& operator<<(std::ostream& os, const Trapezoid<T>& figure) {
        os << "Фигура с " << figure.get_points_count() << " точками:\n";
        for (size_t i = 0; i < figure.get_points_count(); ++i) {
            const auto& p = figure.get_point(i);
            os << "Точка " << i << ": (" << p.getX() << ", " << p.getY() << ")\n";
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Trapezoid<T>& trapezoid) {
        for (int i = 0; i < 4; ++i) {
            T x, y;
            if (!(is >> x >> y)) break;
            trapezoid.add_point(Point<T>(x, y));
        }
        return is;
    }
};


template<class T>
class Rhombus : public Figure<T> {
public:
    Rhombus() {std::cout << "Введите точки для ромба\n";}
    Rhombus(const Rhombus<T>& other) : Figure<T>() {  
        PointContainer<Point<T>> tmp;
        for (size_t i = 0; i < other.get_points_count(); ++i) {
            tmp.push_back(std::make_unique<Point<T>>(other.get_point(i)));
        }
        this->points = std::move(tmp);
    }
    Rhombus(Rhombus<T>&& other) noexcept = default;

    Point<T> center() const {
        const auto &A = this->points[0];
        const auto &C = this->points[2];
        double cx = (A.getX() + C.getX()) / 2.0;
        double cy = (A.getY() + C.getY()) / 2.0;

        return Point<T>(static_cast<T>(cx), static_cast<T>(cy));
    }

    operator double() {
        const size_t n = this->get_points_count();
        double sum = 0.0;
        for (size_t i = 0; i < n; ++i) {
            const auto &p = this->get_point(i);
            const auto &q = this->get_point((i + 1) % n);
            double xi = static_cast<double>(p.getX());
            double yi = static_cast<double>(p.getY());
            double xj = static_cast<double>(q.getX());
            double yj = static_cast<double>(q.getY());
            sum += xi * yj - xj * yi;
        }
        return std::abs(sum) * 0.5;
    }

    friend std::ostream& operator<<(std::ostream& os, const Rhombus<T>& figure) {
        os << "Ромб с " << figure.get_points_count() << " точками:\n";
        for (size_t i = 0; i < figure.get_points_count(); ++i) {
            const auto& p = figure.get_point(i);
            os << "Точка " << i + 1 << ": (" << p.getX() << ", " << p.getY() << ")\n";
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Rhombus<T>& rhombus) {
        for (int i = 0; i < 4; ++i) {
            T x, y;
            if (!(is >> x >> y)) break;
            rhombus.add_point(Point<T>(x, y));
        }
        return is;
    }
};