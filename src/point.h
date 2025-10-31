#include <type_traits>

template<class T>
// Проверка на скалярность типа
concept Pointable = std::is_scalar_v<T>;

template<Pointable T>
class Point {
public:
    Point(T x = T(), T y = T()) : _x(x), _y(y) {}

    T getX() const { return _x; }
    T getY() const { return _y; }
    
private:
    T _x;
    T _y;
};