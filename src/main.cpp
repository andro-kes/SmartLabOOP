#include <iostream>
#include <memory>
#include "figures.h"
#include "array.h"

using namespace std;

int main() {
    cout << "=== Демонстрация работы с фигурами ===" << endl;
    
    Array<shared_ptr<Figure<int>>> figures;
    
    // Создание ромба
    auto rhombus = make_shared<Rhombus<int>>();
    cout << "Введите 4 точки для ромба (x y):" << endl;
    cin >> *rhombus;
    figures.push_back(rhombus);
    
    // Создание трапеции
    auto trapezoid = make_shared<Trapezoid<int>>();
    cout << "Введите 4 точки для трапеции (x y):" << endl;
    cin >> *trapezoid;
    figures.push_back(trapezoid);
    
    // Создание пятиугольника
    auto pentagon = make_shared<Pentagon<int>>();
    cout << "Введите 5 точек для пятиугольника (x y):" << endl;
    cin >> *pentagon;
    figures.push_back(pentagon);
    
    // Вывод информации о фигурах
    cout << "\nИнформация о фигурах" << endl;
    double total_area = 0;
    for (size_t i = 0; i < figures.size(); ++i) {
        cout << "Фигура " << i << ":" << endl;
        cout << *figures[i];
        double area = static_cast<double>(*figures[i]);
        cout << "Площадь: " << area << endl;
        auto center = figures[i]->center();
        cout << "Центр: (" << center.getX() << ", " << center.getY() << ")" << endl;
        total_area += area;
        cout << "------------------------" << "\n";
    }
    
    cout << "Общая площадь всех фигур: " << total_area << endl;
    
    return 0;
}